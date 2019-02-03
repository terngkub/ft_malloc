#include "ft_malloc.h"

void print_node_address(t_malloc_node *curr)
{
    void    *start;
    void    *end;

    while (curr)
    {
        start = (void *)curr + sizeof(t_malloc_node);
        end = start + curr->size;
        printf("%p - %p : %zu bytes\n", start, end, curr->size);
        curr = curr->next;
    }
}

void show_alloc_mem(void)
{
    if (g_malloc_env.tiny)
    {
        printf("TINY %p\n", g_malloc_env.tiny);
        print_node_address(g_malloc_env.tiny->first);
    }
    if (g_malloc_env.small)
    {
        printf("SMALL %p\n", g_malloc_env.small);
        print_node_address(g_malloc_env.small->first);
    }
    if (g_malloc_env.large)
    {
        printf("LARGE %p\n", g_malloc_env.large);
        print_node_address(g_malloc_env.large);
    }
}