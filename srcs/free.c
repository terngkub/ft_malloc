/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:08:46 by nkamolba          #+#    #+#             */
/*   Updated: 2019/02/14 22:51:56 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void	check_map(t_malloc_space *space, t_malloc_map *map)
{
	if (map->used != sizeof(t_malloc_map))
		return ;
	if (map->prev)
		map->prev->next = map->next;
	if (map->next)
		map->next->prev = map->prev;
	if (map == space->map)
	{
		space->map = map->next;
		space->ptr = (space->map) ? (void *)space->map + space->map->used : NULL;
	}
	munmap(map, space->size);
}

static int	free_from_space(t_malloc_space *space, void *ptr)
{
	void			*adj_ptr;
	t_malloc_block	*curr;
	t_malloc_block	*prev;

	write(1, "free space\n", 11);
	if (space->block == NULL)
		return (0);
	adj_ptr = (t_malloc_block *)(ptr - sizeof(t_malloc_block));
	curr = space->block;
	if (curr == adj_ptr)
	{
		write(1, "first\n", 6);
		space->block = curr->next;
		curr->map->used -= curr->size + sizeof(t_malloc_block);
		check_map(space, curr->map);
		return (1);
	}
	curr = curr->next;
	prev = curr;
	while (curr)
	{
		write(1, "loop\n", 5);
		if (curr == adj_ptr)
		{
			write(1, "found\n", 6);
			prev->next = curr->next;
			return (1);
		}
		write(1, "before curr\n", 12);
		curr = curr->next;
		write(1, "before prev\n", 12);
		prev = curr;
		write(1, "next\n", 5);
	}
	write(1, "not found\n", 10);
	return (0);
}

static int	free_large_node(t_malloc_node **node, void *ptr)
{
	void			*adj_ptr;
	t_malloc_node	*curr;
	t_malloc_node	*prev;

	write(1, "free large\n", 11);
	if (node == NULL || *node == NULL)
		return (0);
	adj_ptr = ptr - sizeof(t_malloc_node);
	curr = *node;
	if (curr == adj_ptr)
	{
		write(1, "free first\n", 11);
		if (munmap(curr, calculate_allocate_size(curr->size + sizeof(t_malloc_node))) == -1)
			write(1, "error\n", 6);
		*node = NULL;
		return (1);
	}
	curr = curr->next;
	prev = curr;
	while (curr)
	{
		if (curr == adj_ptr)
		{
			write(1, "free in loop\n", 13);
			prev->next = curr->next;
			if (munmap(curr, calculate_allocate_size(curr->size + sizeof(t_malloc_node))) == -1)
				write(1, "error\n", 6);
			return (1);
		}
		curr = curr->next;
		prev = curr;
	}
	return (0);
}

void		free(void *ptr)
{
	write(1, "my free\n", 8);
	if (ptr == NULL)
		return ;
	if (free_from_space(&g_malloc_env.tiny, ptr))
		return ;
	if (free_from_space(&g_malloc_env.small, ptr))
		return ;
	if (free_large_node(&g_malloc_env.large, ptr))
		return ;
	write(1, "can't find\n", 11);
}
