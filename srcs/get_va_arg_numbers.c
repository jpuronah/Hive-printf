/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_va_arg_numbers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 12:33:45 by jpuronah          #+#    #+#             */
/*   Updated: 2022/07/27 13:19:03 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

void	get_va_arg(t_printf *flags)
{
	intmax_t	number;

	if (flags->num_type & (1 << F_LONG))
		number = (intmax_t)va_arg(flags->args, long);
	else if (flags->num_type & (1 << F_LONGLONG))
		number = (intmax_t)va_arg(flags->args, long long);
	else if (flags->num_type & (1 << F_SHORT))
		number = (intmax_t)((short)va_arg(flags->args, int));
	else if (flags->num_type & (1 << F_SHORTCHAR))
		number = (intmax_t)((char)va_arg(flags->args, int));
	else if (flags->num_type & (1 << F_MAXINT))
		number = (va_arg(flags->args, intmax_t));
	else if (flags->num_type & F_UNSIGNED)
		number = ((intmax_t)va_arg(flags->args, ssize_t));
	else
		number = ((intmax_t)va_arg(flags->args, int));
	if (flags->flag & (1 << F_ZERO))
	{
		if (flags->precision < flags->num_length)
			flags->precision = flags->num_length;
		if (flags->width > flags->precision && flags->flag & (1 << F_PRECISION))
			flags->zero_padding_precision = flags->width - flags->precision;
		flags->precision = ft_max(flags->width, flags->precision);
		flags->padding += flags->zero_padding_precision;
		flags->num_length -= flags->zero_padding_precision;
	}
	if (number < 0 && flags->flag & (1 << F_ZERO) && flags->zero_padding_precision > 0)
		flags->precision++;
	itoa_printf(number, flags, 0);
}

int	get_base(char format)
{
	int	base;

	base = 0;
	if (format == 'b' || format == 'B')
		base = 2;
	if (format == 'o' || format == 'O')
		base = 8;
	if (format == 'u' || format == 'U')
		base = 10;
	if (format == 'x' || format == 'X')
		base = 16;
	return (base);
}

void	get_va_arg_base(char format, t_printf *flags)
{
	uintmax_t	number;
	int			base;

	printf("c: %c, format string: %s\n", format, flags->format_string);
	base = get_base(format);
	if (flags->num_type & (1 << F_LONG))
		number = ((uintmax_t)va_arg(flags->args, unsigned long));
	else if (flags->num_type & (1 << F_LONGLONG))
		number = ((uintmax_t)va_arg(flags->args, unsigned long long));
	else if (flags->num_type & (1 << F_SHORT))
		number = (uintmax_t)((unsigned short)va_arg(flags->args, int));
	else if (flags->num_type & (1 << F_SHORTCHAR))
		number = (uintmax_t)((unsigned char)va_arg(flags->args, int));
	else if (flags->num_type & (1 << F_SIZET))
		number = ((uintmax_t)va_arg(flags->args, size_t));
	else
		number = ((uintmax_t)va_arg(flags->args, unsigned int));
	if (flags->flag & (1 << F_ZERO))
	{
		if (flags->width > flags->precision && flags->flag & (1 << F_PRECISION))
			flags->zero_padding_precision = ft_abs(flags->width - flags->precision);
		flags->precision = ft_max(flags->width, flags->precision);
		flags->padding += flags->zero_padding_precision;
		flags->num_length -= flags->zero_padding_precision;
	}
	printf("number: %jd\n", number);
	itoa_base_printf(number, flags, base);
}

void	get_va_arg_float_double(t_printf *flags)
{
	long double	number;
	long		tmp;
	int			length;
	long double		decimal;
	long		num;

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
	if ((long)decimal % 10 > 4)
		decimal = (decimal) / 10 + 1;
	else
		decimal = (decimal) / 10;
	num = (int)decimal;
	itoa_float_double(number, flags, num);
}
