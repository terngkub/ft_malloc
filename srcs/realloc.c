/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:09:12 by nkamolba          #+#    #+#             */
/*   Updated: 2019/02/08 14:09:14 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void    *reaclloc(void *ptr, size_t size)
{
    t_malloc_node   *node;
    size_t          new_size;
    void            *new_ptr;

    if (ptr == NULL)
        return (NULL);
    node = (t_malloc_node  *)(ptr - sizeof(t_malloc_node));
    new_size = (size < node->size) ? size : node->size;
    if ((new_ptr = malloc(size)))
        return (NULL);
    ft_memcpy(new_ptr, ptr, new_size);
    free(ptr);
    return new_ptr;
}