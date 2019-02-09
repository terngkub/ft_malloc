/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:08:46 by nkamolba          #+#    #+#             */
/*   Updated: 2019/02/09 18:14:07 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static int	free_from_space(t_malloc_space *space, void *ptr)
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

static int	free_malloc_node(void *ptr)
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
	return (0);
}

void		free(void *ptr)
{
	if (free_from_space(g_malloc_env.tiny, ptr))
		return ;
	if (free_from_space(g_malloc_env.small, ptr))
		return ;
	if (free_malloc_node(ptr))
		return ;
}
