/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:51:31 by jpuronah          #+#    #+#             */
/*   Updated: 2021/12/27 18:35:04 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	if (n == -2147483648)
	{
		ft_putchar('-');
		ft_putchar('2');
		ft_putnbr(147483648);
		return ;
	}
	if (n < 0)
	{
		n = -n;
		ft_putchar('-');
	}
	if (n < 10)
		ft_putchar((char)(n + 48));
	else
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
}
