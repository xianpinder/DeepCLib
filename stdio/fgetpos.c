#include <stdio.h>
#include <unistd.h>

#undef fgetpos


int fgetpos (FILE *fp, fpos_t *pos)
{
    long offset;
    unsigned int flags;

	if (fp == NULL)
		return -1;

	flags = fp->_flag;

    /* First find the actual file pointer position */

    offset = lseek (fp->_file, 0, SEEK_CUR);
    if (offset == -1)
		return -1;

    /* If the file is open for writing and the last action was a  */
    /* write then added on the number of characters in the buffer */
    
    if ((flags & _IOWRT) && (flags & _IOLASTW))
	    offset += fp->_cnt;

    /* If the file is open for reading and the last action was a  */
    /* read then subtract the number of characters in the buffer. */
    /* Need to take any 'un-got' characters into account.         */

    if ((flags & _IOREAD) && (flags & _IOLASTR))
    {
        offset -= fp->_cnt;
		if (flags & _IOUCH)
			offset--;
    }

    if (pos == NULL)
        return offset;

    *pos = offset;
    return 0;
}
