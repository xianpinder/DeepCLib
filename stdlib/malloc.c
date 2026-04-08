/*
 * malloc.c
 *
 * Provides: malloc, free
 *
 * Design:
 *   - First-fit allocation from a sorted-address free list
 *   - Coalescing of adjacent free blocks on free()
 *   - Lazy heap initialisation on first malloc() call
 *   - Minimal per-block overhead: one header (size + next pointer)
 *   - Heap/stack collision protection for shared memory
 *
 * Memory layout (heap grows up, stack grows down):
 *
 *     _heap_start                                        _heap_end
 *        |                                                |
 *        v                                                v
 *        +-------------------+~~~~~~~~+-------------------+
 *        | heap (grows up)   | free   |   stack (grows dn)|
 *        +-------------------+~~~~~~~~+-------------------+
 *                                     ^
 *                                     |
 *                                 stack pointer
 *
 * The C startup code must set _heap_start and _heap_end to the
 * bottom and top addresses of the shared memory region.
 * The stack pointer starts at or near _heap_end and grows down.
 */

#include <stddef.h>
#include <string.h>

/* ================================================================== */
/*  Heap boundaries (set by C startup code)                           */
/* ================================================================== */

extern char *_heap_start;
extern char *_heap_end;

/* ================================================================== */
/*  Stack pointer access                                              */
/*                                                                    */
/*  _getstkptr() must be provided as a small assembly routine that    */
/*  returns the current stack pointer value.            			  */
/* ================================================================== */

extern char *_getstkptr(void);

/*
 * STACK_MARGIN: safety margin in bytes between the highest heap
 * allocation and the current stack pointer.  Must be large enough
 * to cover the deepest call chain that might occur between the
 * collision check in malloc() and the caller's use of the pointer.
 * 64 bytes is conservative for typical eZ80 code.
 */
#define STACK_MARGIN   64

/* ================================================================== */
/*  Block header                                                       */
/*                                                                     */
/*  Every block (free or allocated) begins with this header.           */
/*  When a block is free, 'next' points to the next free block.       */
/*  When allocated, 'next' is unused but the space is reserved so     */
/*  that any block can be returned to the free list.                   */
/*                                                                     */
/*  Memory layout of an allocated block:                               */
/*                                                                     */
/*      +--------+--------+-----------------------------+              */
/*      |  size  |  next  |  user data ...              |              */
/*      +--------+--------+-----------------------------+              */
/*      ^                  ^                                           */
/*      |                  +-- pointer returned by malloc              */
/*      +-- block start                                                */
/*                                                                     */
/*  'size' is the total block size including the header.               */
/* ================================================================== */

typedef struct block {
    size_t        size;     /* total size of block including header  */
    struct block *next;     /* next free block (when on free list)   */
} block_t;

#define HEADER_SIZE    sizeof(block_t)

/*
 * Minimum block size: header plus at least one byte of user data.
 * We never create blocks smaller than this, ensuring every block
 * on the free list can actually satisfy a malloc(1) rather than
 * becoming a useless fragment.
 */
#define MIN_BLOCK      (HEADER_SIZE + 1)

/* ================================================================== */
/*  Free list                                                          */
/* ================================================================== */

static block_t *freelist = NULL;    /* head of sorted free list */
static int      heap_ready = 0;     /* nonzero after initialisation */

/*
 * init_heap - create a single free block spanning the entire
 * shared memory region.  The actual usable extent is determined
 * at allocation time by checking the stack pointer.
 */
static void init_heap(void)
{
    size_t heap_size;

    if (_heap_end <= _heap_start ||
        (size_t)(_heap_end - _heap_start) < MIN_BLOCK) {
        /* Heap is too small to be usable */
        freelist = NULL;
        heap_ready = 1;
        return;
    }

    heap_size = (size_t)(_heap_end - _heap_start);

    freelist = (block_t *)_heap_start;
    freelist->size = heap_size;
    freelist->next = NULL;

    heap_ready = 1;
}

/* ================================================================== */
/*  malloc                                                             */
/* ================================================================== */

void *malloc(size_t nbytes)
{
    size_t   total;
    block_t *curr;
    block_t *prev;
    char    *limit;

    if (!heap_ready)
        init_heap();

    if (nbytes == 0)
        return NULL;

    /* Calculate total block size needed (header + user data) */
    total = nbytes + HEADER_SIZE;
    if (total < MIN_BLOCK)
        total = MIN_BLOCK;

    /* Stack limit: highest address we may allocate up to */
    limit = _getstkptr() - STACK_MARGIN;

    /* First-fit search */
    prev = NULL;
    curr = freelist;

    while (curr != NULL) {
        size_t avail;

        /*
         * Determine usable size of this block.  If the block
         * extends into stack territory, cap its available size.
         * The block's actual size is not changed -- the upper
         * memory remains tracked in the remainder after a split.
         */
        avail = curr->size;
        if ((char *)curr + avail > limit) {
            if ((char *)curr >= limit)
                avail = 0;
            else
                avail = (size_t)(limit - (char *)curr);
        }

        if (avail >= total) {
            /* Found a usable block */

            if (curr->size >= total + MIN_BLOCK) {
                /*
                 * Split from the beginning: allocate 'total' bytes
                 * at the start of this block and create a remainder
                 * block above it.  The remainder retains the full
                 * upper extent of the original block, including any
                 * portion currently in stack territory.  This means
                 * the memory becomes available again if the stack
                 * recedes.
                 */
                block_t *remainder;

                remainder = (block_t *)((char *)curr + total);
                remainder->size = curr->size - total;
                remainder->next = curr->next;

                if (prev != NULL)
                    prev->next = remainder;
                else
                    freelist = remainder;

                curr->size = total;
                return (void *)((char *)curr + HEADER_SIZE);
            } else {
                /* Use the entire block (too small to split) */
                if (prev != NULL)
                    prev->next = curr->next;
                else
                    freelist = curr->next;

                return (void *)((char *)curr + HEADER_SIZE);
            }
        }

        prev = curr;
        curr = curr->next;
    }

    /* No suitable block found */
    return NULL;
}

/* ================================================================== */
/*  free                                                               */
/* ================================================================== */

void free(void *ptr)
{
    block_t *blk;
    block_t *curr;
    block_t *prev;

    if (ptr == NULL)
        return;

    /* Step back past the header to get the block pointer */
    blk = (block_t *)((char *)ptr - HEADER_SIZE);

    /*
     * Insert into the free list in address order.
     * This allows us to coalesce adjacent blocks.
     */
    prev = NULL;
    curr = freelist;

    while (curr != NULL && curr < blk) {
        prev = curr;
        curr = curr->next;
    }

    /* Insert blk between prev and curr */
    blk->next = curr;
    if (prev != NULL)
        prev->next = blk;
    else
        freelist = blk;

    /*
     * Coalesce with the next block if adjacent.
     * Two blocks are adjacent when one ends exactly where the
     * next begins: (char*)blk + blk->size == (char*)curr
     */
    if (curr != NULL &&
        (char *)blk + blk->size == (char *)curr) {
        blk->size += curr->size;
        blk->next = curr->next;
    }

    /*
     * Coalesce with the previous block if adjacent.
     */
    if (prev != NULL &&
        (char *)prev + prev->size == (char *)blk) {
        prev->size += blk->size;
        prev->next = blk->next;
    }
}
