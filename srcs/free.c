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
#include <stdio.h>

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

	printf("node: %p, curr: %p\n", *node, ptr);
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

void		free(void *ptr)
{
	void	*adj_ptr;

	printf("ptr: %p\n", ptr);
	if (ptr == NULL)
		return ;
	adj_ptr = ptr - sizeof(t_malloc_node);
	if (free_node(&g_malloc_env.tiny.block, adj_ptr, 0))
		return ;
	if (free_node(&g_malloc_env.small.block, adj_ptr, 0))
		return ;
	if (free_node(&g_malloc_env.large, adj_ptr, 1))
		return ;
	write(1, "can't find\n", 11);
}
