/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_double_pointer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 10:48:02 by jpuronah          #+#    #+#             */
/*   Updated: 2022/07/27 14:09:31 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

static char	check_flags(t_printf *flags, char *string, long double number)
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

void	itoa_float_double(long double number, t_printf *flags, long num)
{
	int		length;
	int		accuracy;
	char	*string;

	string = NULL;
	length = flags->num_length - 1 - flags->precision;
	accuracy = flags->num_length - 1 - length;
	string = ft_memalloc((size_t)(accuracy + length + 1));
	while (accuracy--)
	{
		string[length + accuracy + 1] = (num % 10 + '0');
		num /= 10;
	}
	if (flags->precision > 0)
		string[length] = '.';
	num = ft_abs_long_long((long long)number);
	while (++accuracy < length)
	{
		string[length - accuracy - 1] = num % 10 + '0';
		num /= 10;
	}
	string[0] = check_flags(flags, string, number);
	printf_write(flags, string, (size_t)flags->num_length);
	free(string);
	string = NULL;
}

long double	get_decimal(t_printf *flags, long double number)
{
	long double		decimal;

	if (number < 0)
		flags->num_length++;
	decimal = number;
	if (number < 0)
		decimal *= -1;
	if ((long)number < 0.0f)
		decimal = (decimal + ((long)number)) * ft_pow(10, flags->precision + 1);
	else
		decimal = (decimal - ((long)number)) * ft_pow(10, flags->precision + 1);
	if ((long)decimal % 10 > 4)
		decimal = (decimal) / 10 + 1;
	else
		decimal = (decimal) / 10;
	return (decimal);
}

void	get_va_arg_float_double(t_printf *flags)
{
	long double		number;
	long			tmp;
	int				length;
	long			num;

	if (flags->flag & (1 << F_LONG))
		number = (long double)(va_arg(flags->args, long double));
	else
		number = (long double)(va_arg(flags->args, double));
	if (flags->flag & (1 << F_ZERO))
		flags->precision = flags->width;
	if (~flags->flag & (1 << F_PRECISION))
		flags->precision = 6;
	if (flags->precision > 0)
		length = 1;
	tmp = ft_abs_long_long((long long)number);
	while (tmp)
	{
		tmp /= 10;
		flags->num_length = flags->precision + (++length);
	}
	num = (int)get_decimal(flags, number);
	itoa_float_double(number, flags, num);
}

void	print_pointer_address(t_printf *flags)
{
	void	*pointer;

	pointer = va_arg(flags->args, void *);
	flags->flag &= ~(1 << F_PREFIX);
	if (flags->flag & (1 << F_ZERO))
		flags->width -= 2;
	if (flags->num_length > flags->width - 3)
		flags->padding = flags->width - 3 - flags->num_length;
	flags->flag |= (1 << F_PREFIX);
	flags->flag |= (1 << F_POINTER);
	itoa_base_printf((uintmax_t)pointer, flags, 16);
	flags->flag = 0;
}
