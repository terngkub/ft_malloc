/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:09:00 by nkamolba          #+#    #+#             */
/*   Updated: 2019/02/09 19:59:26 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void    *do_mmap(size_t size)
{
	void	*ptr;
	size_t	allocate_size;

	allocate_size = calculate_allocate_size(size);
	ptr = mmap(NULL, allocate_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, 0, 0);
	if (ptr == MAP_FAILED)
		return NULL;
	return (ptr);
}

void	*init_space(size_t size, t_malloc_space *next)
{
	void			*ptr;
	t_malloc_space	space;

	ptr = do_mmap(size);
	space.first = NULL;
	space.used = 0;
	space.size = size;
	space.next = next;
	ft_memcpy(ptr, &space, sizeof(t_malloc_space));
	return (ptr);
}

void    *add_to_space(t_malloc_space **space, size_t space_size, size_t malloc_size)
{
	t_malloc_space	*new_space;
	t_malloc_node   node;

	if (*space == NULL)
		*space = init_space(space_size, NULL);
	// used size + new size is more than space_size
	// create new space, set next to be old space,
	if ((*space)->used + malloc_size + sizeof(t_malloc_node) < (*space)->size)
	{
		new_space = init_space(space_size, *space);
		
		
	}
	node.size = malloc_size;
	if ((*space)->first == NULL)
	{
		node.next = NULL;
		(*space)->first = (t_malloc_node *)((void *)*space + sizeof(t_malloc_space));
	}
	else
	{
		node.next = (*space)->first;
		(*space)->first = (t_malloc_node *)((void *)(*space)->first + sizeof(t_malloc_node) + (*space)->first->size);
	}
	ft_memcpy((*space)->first, &node, sizeof(t_malloc_node));
	return ((void *)(*space)->first + sizeof(t_malloc_node));
}

void	*add_large_node(size_t size)
{
	void			*ptr;
	t_malloc_node	node;

	ptr = do_mmap(size + sizeof(t_malloc_node));
	node.size = size;
	node.next = g_malloc_env.large;
	g_malloc_env.large = (t_malloc_node *)ptr;
	ft_memcpy(ptr, &node, sizeof(t_malloc_node));
	return (ptr + sizeof(t_malloc_node));
}

void	*malloc(size_t size)
{
	if (size < TINY_MALLOC_SIZE)
		return (add_to_space(&(g_malloc_env.tiny), size, TINY_SPACE_SIZE));
	else if (size < SMALL_MALLOC_SIZE)
		return (add_to_space(&(g_malloc_env.small), size, SMALL_SPACE_SIZE));
	return add_large_node(size);
}
