#include "ft_malloc.h"

int		main(void)
{
	char	*str1;
	char	*str2;
	char	*str3;
	char	*str4;
	char	*str5;
	char	*str6;

	str1 = (char *)malloc(12);
	str2 = (char *)malloc(20);
	str3 = (char *)malloc(80);
	str4 = (char *)malloc(500);
	str5 = (char *)malloc(100);
	str6 = (char *)malloc(500);

	show_alloc_mem();

	free(str1);
	free(str2);
	free(str3);
	free(str4);
	free(str5);
	free(str6);

	return (0);
}