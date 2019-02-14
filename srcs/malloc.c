/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:09:00 by nkamolba          #+#    #+#             */
/*   Updated: 2019/02/14 18:12:17 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void	*do_mmap(size_t size)
{
	void	*ptr;
	size_t	allocate_size;

	allocate_size = calculate_allocate_size(size);
	ptr = mmap(NULL, allocate_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, 0, 0);
	if (ptr == MAP_FAILED)
		return NULL;
	return (ptr);
}

static void	*add_block(t_malloc_space *space, size_t malloc_size)
{
	t_malloc_block	block;
	void			*ptr;

	block.size = malloc_size;
	block.next = space->block;
	ft_memcpy(space->ptr, &block, sizeof(t_malloc_node));
	ptr = space->ptr + sizeof(t_malloc_node);
	space->block = space->ptr;
	space->ptr += sizeof(t_malloc_node) + malloc_size;
	space->map->used += sizeof(t_malloc_node) + malloc_size;
	return (ptr);
}

static void	add_map(t_malloc_space *space)
{
	t_malloc_map	map;
	t_malloc_map	*ptr;

	if ((ptr = do_mmap(space->size)) == NULL)
	{
		write(1, "error\n", 6);
		return ;
	}
	map.used = sizeof(t_malloc_map);
	map.prev = NULL;
	map.next = space->map;
	ft_memcpy(ptr, &map, sizeof(t_malloc_map));
	if (space->map)
		space->map->prev = ptr;
	space->map = ptr;
	space->ptr = (void *)space->map + sizeof(t_malloc_map);
}

static void	init_space(t_malloc_space *space, size_t size)
{
	space->block = NULL;
	space->ptr = (void *)space->map + sizeof(t_malloc_node);
	space->size = size;
	add_map(space);
}

static void	*add_to_space(t_malloc_space *space, size_t malloc_size, size_t space_size)
{
	if (space->map == NULL)
		init_space(space, space_size);
	if (space->map->used + malloc_size + sizeof(t_malloc_node) > space->size)
		add_map(space);
	return (add_block(space, malloc_size));
}

static void	*add_large_node(size_t size)
{
	void			*ptr;
	t_malloc_node	node;

	ptr = do_mmap(size + sizeof(t_malloc_node));
	node.size = size;
	node.next = g_malloc_env.large;
	ft_memcpy(ptr, &node, sizeof(t_malloc_node));
	g_malloc_env.large = (t_malloc_node *)ptr;
	return (ptr + sizeof(t_malloc_node));
}

void		*malloc(size_t size)
{
	if (size <= TINY_MALLOC_SIZE)
		return (add_to_space(&g_malloc_env.tiny, size, TINY_SPACE_SIZE));
	else if (size <= SMALL_MALLOC_SIZE)
		return (add_to_space(&g_malloc_env.small, size, SMALL_SPACE_SIZE));
	return add_large_node(size);
}