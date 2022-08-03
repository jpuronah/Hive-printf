/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 22:49:58 by jpuronah          #+#    #+#             */
/*   Updated: 2022/08/03 22:50:21 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "includes/printf.h"

int	main(int ac, char **av)
{
	int	ret;

	printf("own printf:\n");
	ret = ft_printf("% d", 42);
	printf("|\nret: %d\n", ret);
	printf("\n**********************\n");
	printf("\nreal printf:\n");
	ret = printf("% d", 42);
	printf("|\nret: %d\n", ret);
	printf("\n**********************\n");
	return (0);
}
