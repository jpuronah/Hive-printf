/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 22:49:58 by jpuronah          #+#    #+#             */
/*   Updated: 2022/08/05 14:15:21 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "includes/printf.h"

int	main(int ac, char **av)
{
	int	ret;

	int		a = -4;
	int		b = 0;
	char	c = 'a';
	int		d = 2147483647;
	int		e = -2147483648;
	int		f = 42;
	int		g = 25;
	int		h = 4200;
	int		i = 8;
	int		j = -12;
	int		k = 123456789;
	int		l = 0;
	int		m = -12345678;
	char	*n = "abcdefghijklmnop";
	char	*o = "-a";
	char	*p = "-12";
	char	*q = "0";
	char	*r = "%%";
	char	*s = "-2147483648";
	char	*t = "0x12345678";
	char	*u = "-0";



	printf("own printf:\n");
	ret = ft_printf("%s", -2);
	printf("|\nret: %d\n", ret);
	printf("\n**********************\n");
	printf("\nreal printf:\n");
	ret = printf("%s", -2);
	printf("|\nret: %d\n", ret);
	printf("\n**********************\n");
	return (0);
}
