/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 10:48:02 by jpuronah          #+#    #+#             */
/*   Updated: 2022/07/20 18:50:08 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

static char	check_flags(t_printf *flags, char *string, double number)
{
	char	tmp;

	tmp = string[0];
	if (flags->flag & (1 << F_PRECISION) && flags->flag & (1 << F_ZERO))
		tmp = ' ';
	if (flags->flag & (1 << F_SPACE))
		tmp = ' ';
	if (number < 0)
		tmp = '-';
	if (flags->flag & (1 << F_PLUS) && number >= 0)
		tmp = '+';
	return (tmp);
}

static void	long_double_float_toa_fill(double number, t_printf *flags, long num)
{
	int		length;
	int		accuracy;
	char	*string;

	string = NULL;
	length = flags->num_length - 1 - flags->precision;
	accuracy = flags->num_length - 1 - length;
	string = ft_memalloc(accuracy + length);
	while (accuracy)
	{
		string[length + accuracy] = (char)(num % 10 + '0');
		num /= 10;
		accuracy--;
	}
	if (flags->precision > 0)
		string[length] = '.';
	num = ft_abs_ll((long long)number);
	while (accuracy < length)
	{
		string[length - accuracy - 1] = num % 10 + '0';
		num /= 10;
		accuracy++;
	}
	string[0] = check_flags(flags, string, number);
	printf_write(flags, string, (size_t)flags->num_length);
	free(string);
	string = NULL;
}

void	get_va_arg_float_double(t_printf *flags)
{
	double	number;
	long	tmp;
	int		length;
	double	decimal;
	long	num;

	number = (double)va_arg(flags->args, double);
	if (flags->flag & (1 << F_ZERO))
		flags->precision = flags->width;
	if (~flags->flag & (1 << F_PRECISION))
		flags->precision = 6;
	if (flags->precision > 0)
		length = 1;
	tmp = ft_abs_ll((long long)number);
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
	if ((long)number < 0.0f)
		decimal = (decimal + ((long)number)) * ft_pow(10, flags->precision + 1);
	else
		decimal = (decimal - ((long)number)) * ft_pow(10, flags->precision + 1);
	//decimal = (decimal - (long)(((number < 0.0f) ? -number : number))) * ft_pow(10, flags->precision + 1);
	if ((long)decimal % 10 > 4)
		decimal = (decimal) / 10 + 1;
	else
		decimal = (decimal) / 10;
	//decimal = ((long)decimal % 10 > 4) ? (decimal) / 10 + 1 : decimal / 10;
	num = (int)decimal;
	long_double_float_toa_fill(number, flags, num);
}
