#include <stdlib.h>
#include <string.h>

typedef struct block {
    size_t        size;     /* total size of block including header  */
    struct block *next;     /* next free block (when on free list)   */
} block_t;

#define HEADER_SIZE    sizeof(block_t)

void *realloc(void *ptr, size_t nbytes)
{
    block_t *blk;
    size_t   old_user_size;
    size_t   copy_size;
    void    *newptr;

    if (ptr == NULL)
        return malloc(nbytes);

    if (nbytes == 0)
	{
        free(ptr);
        return NULL;
    }

    blk = (block_t *)((char *)ptr - HEADER_SIZE);
    old_user_size = blk->size - HEADER_SIZE;

    /* If the existing block is already big enough, keep it */
    if (old_user_size >= nbytes)
        return ptr;

    /* Allocate a new block, copy, and free the old one */
    newptr = malloc(nbytes);
    if (newptr == NULL)
        return NULL;

    copy_size = (old_user_size < nbytes) ? old_user_size : nbytes;
    memcpy(newptr, ptr, copy_size);
    free(ptr);

    return newptr;
}
