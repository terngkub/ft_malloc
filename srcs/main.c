/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:08:53 by nkamolba          #+#    #+#             */
/*   Updated: 2019/02/14 22:25:06 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	my_test(void)
{
	char	*str1;
	char	*str2;
	char	*str3;
	char	*str4;
	char	*str5;
	char	*str6;

	str1 = (char *)malloc(12);
	str2 = (char *)malloc(20);
	str3 = (char *)malloc(500);
	str4 = (char *)malloc(800);
	str5 = (char *)malloc(409600);
	str6 = (char *)malloc(10000);

	//show_alloc_mem();
	//str5 = reaclloc(str5, 6000);
	//show_alloc_mem();

/*
	free(str1);
	free(str2);
	free(str3);
	free(str4);
	free(str5);
	free(str6);
	*/
}

void	test_0(void)
{
	int		i;
	char	*addr;

	i = 0;
	while (i < 1024)
		i++;
}

void	test_1(void)
{
	int		i;
	char	*addr;

	i = 0;
	while (i < 1024)
	{
		addr = (char *)malloc(1024);
		addr[0] = 42;
		i++;
	}
}

void	test_2(void)
{
	int		i;
	char	*addr;

	i = 0;
	while (i < 1024)
	{
		addr = (char *)malloc(1024);
		addr[0] = 42;
		free(addr);
		i++;
	}
}

void	test_free()
{
	char	*str1;
	//char	*str2;

	str1 = (char *)malloc(4096*10);
	for (int i = 0; i < 4096*10; i++)
	{
		str1[i] = 'a';
	}
	/*
	str2 = (char *)malloc(4096*1000);
	str2[0] = 43;
	str2[4096 * 1000 - 1] = 43;
	*/
	free(str1);
	free(str1);
	//free(str2);
}

void	test_munmap()
{
	void	*ptr;
	size_t	size = 4096*1000;

	ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, 0, 0);
	if (ptr == MAP_FAILED)
	{
		printf("error mmap\n");
		return ;
	}
	for (int i = 0; i < size; i++)
	{
		((char *)ptr)[i] = 'a';
	}
	/*
	if (munmap(ptr, size) == -1)
	{
		printf("error munmap\n");
		return ;
	}
	*/
	ptr = NULL;
}

int		main(void)
{
	//my_test();
	//test_2();
	//test_free();
	test_munmap();
	return (0);
}