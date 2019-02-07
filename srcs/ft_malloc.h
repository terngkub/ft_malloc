#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stdio.h>
# include <string.h>
# include <sys/mman.h>
# include <unistd.h>

# define TINY_MALLOC_SIZE 4096
# define TINY_LIST_SIZE 4096 * 100

# define SMALL_MALLOC_SIZE 4096 * 4
# define SMALL_LIST_SIZE 4096 * 400

typedef struct				s_malloc_node
{
	size_t					size;
	struct s_malloc_node	*next;
}							t_malloc_node;

typedef struct				s_malloc_space
{
	t_malloc_node			*first;
	size_t					size;
}							t_malloc_space;

typedef struct				s_malloc_env
{
	t_malloc_space			*tiny;
	t_malloc_space			*small;
	t_malloc_node			*large;
}							t_malloc_env;

t_malloc_env				g_malloc_env;

void    		            *malloc(size_t size);
void						free(void *ptr);
void					    *reaclloc(void *ptr, size_t size);
void						show_alloc_mem(void);

void						*ft_memcpy(void *dst, const void *src, size_t n);
size_t						calculate_allocate_size(size_t size);

#endif