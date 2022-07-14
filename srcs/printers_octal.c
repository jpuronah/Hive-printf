/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers_octal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:08:14 by jpuronah          #+#    #+#             */
/*   Updated: 2022/07/14 12:17:46 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	ft_print_float_double(t_printf *flags)
{
	if (flags)
		exit(0);
	exit(1);
}
/*
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
	str = ft_itoa_long_long(octal);
	return (str);
}*/

// 	unsigned int as a hexadecimal number. x uses lower-case letters and X uses upper-case. 
/*void	ft_print_octal(t_printf *flags)
{
	int		integer;
	int		index;
	char	*charteger;

	index = 0;
	integer = va_arg(flags->args, int);
	charteger = ft_itoa_octal(integer);
	flags->wordlen = ft_strlen(charteger);
	if ((flags->wordlen - flags->precision) > 0)
	{
		flags->padding = (flags->padding_length - flags->wordlen);
		if (flags->flag & (1 << F_PREFIX))
			flags->padding--;
	}
	else
		flags->padding = 0;
	padding(flags, 0);
	while (charteger[index])
	{
		if (index == 0 && flags->flag & (1 << F_PREFIX))
			flags->length_written += write(1, "0", 1);
		flags->length_written += write(1, &charteger[index], 1);
		index++;
	}
	padding(flags, 1);
	free(charteger);
	charteger = NULL;
}*/


/*
void	ft_print_octal(t_printf *flags)
{
	int		integer;
	int		index;
	char	*charteger;

	index = 0;
	integer = va_arg(flags->args, int);
	charteger = ft_itoa_octal(integer);
	flags->wordlen = ft_strlen(charteger);
	//printf("%d\n", flags->padding);
	flags->padding = (flags->width - flags->wordlen);// + flags->precision);
	if (flags->flag & (1 << F_PREFIX))
		flags->padding--;
	//printf("padding: %d, width %d, precision %d\n", flags->padding, flags->width, flags->precision);
	if (flags->padding < 0)
		flags->padding = 0;
	padding(flags, 0);
	//printf("%d\n", flags->precision);
	//printf("|%s|\n", charteger);
	if (flags->precision == 0)
		flags->precision = -1;
	//if (flags->precision > flags->wordlen)
	while (charteger[index] && flags->precision--)
	{
		if (index == 0 && flags->flag & (1 << F_PREFIX))
			flags->length_written += write(1, "0", 1);
		flags->length_written += write(1, &charteger[index], 1);
		index++;
	}
	padding(flags, 1);
	free(charteger);
	charteger = NULL;
}
*/