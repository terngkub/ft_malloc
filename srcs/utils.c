#include "ft_malloc.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	while (n--)
		*d++ = *s++;
	return (dst);
}

size_t	calculate_allocate_size(size_t size)
{
	size_t  pagesize;
	
	pagesize = getpagesize();
	if (size % pagesize == 0) 
		return size;
	return (((size / pagesize) + 1) * pagesize);
}