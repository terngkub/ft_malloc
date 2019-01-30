#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

typedef struct		s_alloc
{
	void			*ptr;
	size_t			size;
	struct s_alloc	*prev;
	struct s_alloc	*next;
}					t_alloc;

typedef struct		s_malloc
{
	t_alloc			*tiny;
}					t_malloc;

t_malloc g_malloc;

void	*malloc(size_t size)
{
	void	*region;
	size_t	allocate_size;

	allocate_size = calculate_allocate_size(size);
	region = mmap(NULL, allocate_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, 0, 0);
	if (region == MAP_FAILED)
		return NULL;
	return (region);
}

/*
size_t	calculate_allocate_size(size_t size)
{
	size_t  pagesize;
	
	pagesize = getpagesize();
	if (size % pagesize == 0) 
		return size;
	return (((size / pagesize) + 1) * pagesize);
}

void	*malloc(size_t size)
{
	void	*region;
	size_t	allocate_size;

	allocate_size = calculate_allocate_size(size);
	region = mmap(NULL, allocate_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, 0, 0);
	if (region == MAP_FAILED)
		return NULL;
	return (region);
}

void	free(void *ptr)
{
	if (free == NULL)
		return ;
	munmap(ptr, );
}
*/

int		main(void)
{
	char *str;

	str = malloc(10);
	strcpy(str, "abc\0");
	printf("%s\n", str);
	return (0);
}