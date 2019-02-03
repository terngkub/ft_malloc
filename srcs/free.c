#include "ft_malloc.h"

int	free_from_space(t_malloc_space *space, void *ptr)
{
	void			*adj_ptr;
	t_malloc_node	*curr;
	t_malloc_node	*prev;

	if (space == NULL || space->first == NULL)
		return (0);
	adj_ptr = ptr - sizeof(t_malloc_node);
	curr = space->first;
	if (curr == adj_ptr)
	{
		space->first = curr->next;
		curr->size = 0;
		curr->next = NULL;
		return (1);
	}
	prev = curr;
	curr = curr->next;
	while (curr)
	{
		if (curr == adj_ptr)
		{
			prev->next = curr->next;
			curr->size = 0;
			curr->next = NULL;
			return (1);
		}
		prev = curr;
		curr = curr->next;
	}
	return (0);
}

int	free_malloc_node(void *ptr)
{
	t_malloc_node	*curr;
	t_malloc_node	*prev;
	void			*adj_ptr;

	curr = g_malloc_env.large;
	if (curr == NULL)
		return (0);
	adj_ptr = ptr - sizeof(t_malloc_node);
	if (curr == adj_ptr)
	{
		g_malloc_env.large = curr->next;
		curr->next = NULL;
		munmap(curr, calculate_allocate_size(curr->size));
		return (1);
	}
	prev = curr;
	curr = curr->next;
	while (curr)
	{
		if (curr == adj_ptr)
		{
			prev->next = curr->next;
			curr->next = NULL;
			munmap(curr, calculate_allocate_size(curr->size));
			return (1);
		}
		prev = curr;
		curr = curr->next;
	}
	write(1, "here\n", 5);
	return (0);
}

void    free(void *ptr)
{
	if (free_from_space(g_malloc_env.tiny, ptr))
		return ;
	if (free_from_space(g_malloc_env.small, ptr))
		return ;
	if (free_malloc_node(ptr))
		return ;
	write(1, "error\n", 6);
}