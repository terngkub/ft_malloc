#include "ft_malloc.h"

void    *reaclloc(void *ptr, size_t size)
{
    free(ptr);
    return malloc(size);
}