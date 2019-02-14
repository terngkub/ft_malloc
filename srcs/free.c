/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:08:46 by nkamolba          #+#    #+#             */
/*   Updated: 2019/02/14 18:24:32 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/*
static int	clean_node(t_malloc_node *node, int is_large)
{
	node->next = NULL;
	if (is_large)
		munmap(node, calculate_allocate_size(node->size));
	return (1);
}

static int	free_node(t_malloc_node **node, void *ptr, int is_large)
{
	t_malloc_node	*curr;
	t_malloc_node	*prev;

	if (node == NULL || *node == NULL)
		return (0);
	curr = *node;
	if (curr == ptr)
	{
		*node = curr->next;
		return (clean_node(curr, is_large));
	}
	curr = curr->next;
	prev = curr;
	while (curr)
	{
		if (curr == ptr)
		{
			prev->next = curr->next;
			return (clean_node(curr, is_large));
		}
		curr = curr->next;
		prev = curr;
	}
	return (0);
}
*/

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

int	free_from_space(t_malloc_space *space, void *ptr)
{
	t_malloc_block	*curr;
	t_malloc_block	*prev;

	curr = space->block;
	if (curr == ptr)
	{
		space->block = curr->next;
		curr->map->used -= curr->size + sizeof(t_malloc_block);
		check_map(space, curr->map);
	}
	curr = curr->next;
	prev = curr;
	while (curr)
	{
		if (curr == ptr)
			prev->next = curr->next;
		curr = curr->next;
		prev = curr;
	}
	return (0);
}

/*
void		free(void *ptr)
{
	void	*adj_ptr;

	if (ptr == NULL)
		return ;
	adj_ptr = ptr - sizeof(t_malloc_node);
	if (free_from_space(&g_malloc_env.tiny, adj_ptr))
		return ;
	if (free_from_space(&g_malloc_env.small, adj_ptr))
		return ;
	if (free_node(&g_malloc_env.large, adj_ptr, 1))
		return ;
	write(1, "can't find\n", 11);
}
*/
