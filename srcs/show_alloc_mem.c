#include "ft_malloc.h"

void    print_address_digit(long laddr, int i)
{
    char    *char_list;

    char_list = "0123456789abcdef";
    if (i < 16)
    {
        print_address_digit(laddr / 16, ++i);
        write(1, &char_list[laddr % 16], 1);
    }
}

void    print_address(void *addr)
{
    write(1, "0x", 2);
    print_address_digit((long)addr, 0);
}

void    print_size(size_t size)
{
    char value;

    if (size > 0)
    {
        print_size(size / 10);
        value = size % 10 + '0';
        write(1, &value, 1);
    }
}

void    print_node_address(t_malloc_node *curr)
{
    void    *start;
    void    *end;

    if (curr)
    {
        print_node_address(curr->next);
        start = (void *)curr + sizeof(t_malloc_node);
        end = start + curr->size;
        print_address(start);
        write(1, " - ", 3);
        print_address(end);
        write(1, " : ", 3);
        print_size(curr->size);
        write(1, " bytes\n", 7);

    }
}

void show_alloc_mem(void)
{
    if (g_malloc_env.tiny)
    {
        write(1, "TINY ", 5);
        print_address(g_malloc_env.tiny);
        write(1, "\n", 1);
        print_node_address(g_malloc_env.tiny->first);
    }
    if (g_malloc_env.small)
    {
        write(1, "SMALL ", 6);
        print_address(g_malloc_env.small);
        write(1, "\n", 1);
        print_node_address(g_malloc_env.small->first);
    }
    if (g_malloc_env.large)
    {
        write(1, "LARGE ", 6);
        print_address(g_malloc_env.large);
        write(1, "\n", 1);
        print_node_address(g_malloc_env.large);
    }
}