/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 10:48:02 by jpuronah          #+#    #+#             */
/*   Updated: 2022/07/12 20:51:32 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

double	ft_pow(double n, int pow)
{
	return (pow ? n * ft_pow(n, pow - 1) : 1);
}

static void	long_double_float_toa_fill(double number, t_printf *flags, long value)
{
	int		length;
	int		accuracy;
	char	string[48];

	length = flags->num_length - 1 - flags->precision;
	accuracy = flags->num_length - 1 - length;
	//printf("accu: %d, length: %d, value: %ld, numlen: %d\n", accuracy, length, value, flags->num_length);
	while (accuracy)
	{
		string[length + accuracy + 1] = value % 10 + '0';
		value /= 10;
		accuracy--;
	}
	//printf("string: |%s|\n", string);
	if (flags->precision > 0)
		string[length] = '.';
	value = ft_abs_ll(number);
	while (accuracy < length)
	{
		string[length - accuracy - 1] = value % 10 + '0';
		value /= 10;
		accuracy++;
	}
	if (flags->flag & (1 << F_PRECISION) && flags->flag & (1 << F_ZERO))
		string[0] = ' ';
	if (flags->flag & (1 << F_SPACE))
		string[0] = ' ';
	if (number < 0)
		string[0] = '-';
	if (flags->flag & (1 << F_PLUS) && number >= 0)
		string[0] = '+';
	printf_write(flags, string, flags->num_length);
}

void	parse_va_arg_type_numbers_float_double(t_printf *flags)
{
	double	number;
	long	tmp;
	int		length;
	double	decimal;
	long	value;

	number = (double)va_arg(flags->args, double);
	if (flags->flag & (1 << F_ZERO))
		flags->precision = flags->width;
	if (~flags->flag & (1 << F_PRECISION))
		flags->precision = 6;
	if (flags->precision > 0)
		length = 1;
	tmp = ft_abs_ll(number);
	while (tmp)
	{
		tmp /= 10;
		length++;
	}
	if (flags->flag & (1 << F_ZERO))
		flags->precision = flags->width;
	flags->num_length = flags->precision + length;
	if (number < 0)
		flags->num_length++;
	decimal = number;
	if (number < 0)
		decimal *= -1;
	decimal = decimal - (long)number * ft_pow(10, flags->precision + 1);
	decimal = ((long)decimal % 10 > 4) ? (decimal) / 10 + 1 : decimal / 10;
	value = (int)decimal;
	long_double_float_toa_fill(number, flags, value);
}
