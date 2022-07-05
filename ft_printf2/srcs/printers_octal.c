/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers_octal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:08:14 by jpuronah          #+#    #+#             */
/*   Updated: 2022/07/05 16:56:53 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

char	*ft_itoa_octal(int num)
{
	char		*str;
	long int	i;
	int			res;
	long int	octal;

	res = 0;
	i = 1;
	octal = 0;
	while (num != 0)
	{
		res = num % 8;
		num = num / 8;
		octal = octal + (res * i);
		i = i * 10;
	}
	//printf("%ld\n", octal);
	str = ft_itoa_long_long(octal);
	//str = ft_litoa_base(octal, 10);
	return (str);
}

// 	unsigned int as a hexadecimal number. x uses lower-case letters and X uses upper-case. 
void	ft_print_octal(t_printf *flags)
{
	int		integer;
	int		index;
	char	*charteger;
	//char	caps;

	index = 0;
	integer = va_arg(flags->args, int);
	charteger = ft_itoa_octal(integer);
	flags->wordlen = ft_strlen(charteger);
	if ((flags->wordlen - flags->precision) > 0)
		flags->padding = (flags->length - flags->wordlen);
	else
		flags->padding = 0;
	padding(flags, 0);
	while (charteger[index])
	{
		if (index == 0 && flags->flag & (1 << F_PREFIX))
			flags->total_length += write(1, "0", 1);
		flags->total_length += write(1, &charteger[index], 1);
		index++;
	}
	padding(flags, 1);
	free(charteger);
	charteger = NULL;
}
