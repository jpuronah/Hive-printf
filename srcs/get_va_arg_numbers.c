/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_va_arg_numbers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 12:33:45 by jpuronah          #+#    #+#             */
/*   Updated: 2022/09/30 11:31:40 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

static void	check_for_zero_flag(t_printf *flags, intmax_t number)
{
	if (flags->flag & (1 << F_ZERO))
	{
		if (flags->flag & (1 << F_PRECISION) && flags->width > flags->precision)
		{
			if (flags->precision < flags->num_length)
				flags->precision = flags->num_length;
			flags->zero_pad_precision = flags->width - flags->precision;
			if (number < 0)
			{
				flags->num_length++;
				flags->precision++;
			}
		}
		if (number < 0 && flags->flag & (1 << F_PRECISION) && flags->width < flags->precision && flags->width < flags->num_length)
			flags->precision++;
		flags->precision = ft_max(flags->width, flags->precision);
		flags->padding += flags->zero_pad_precision;
		flags->num_length -= flags->zero_pad_precision;
		if (number < 0 && flags->zero_pad_precision > 0)
			flags->precision++;
	}
}

void	get_number_length(t_printf *flags, intmax_t number)
{
	intmax_t	tmp;

	tmp = number;
	if (tmp > 0)
	{
		while (tmp > 0)
		{
			tmp /= 10;
			flags->num_length++;
		}
	}
	else if (tmp < 0)
	{
		while (tmp < 0)
		{
			tmp /= 10;
			flags->num_length++;
		}
	}
}

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
	get_number_length(flags, number);
	check_for_zero_flag(flags, number);
	itoa_printf(number, flags, 0);
}

static void	check_for_zero_flag_base(t_printf *flags, uintmax_t number)
{
	if (flags->flag & (1 << F_ZERO))
	{
		if (flags->width > flags->precision && flags->flag & (1 << F_PRECISION))
			flags->zero_pad_precision = flags->width - flags->precision;
		if (flags->precision == 0)
			flags->precision = ft_max(flags->width, flags->precision);
		flags->padding += flags->zero_pad_precision;
		flags->num_length -= flags->zero_pad_precision;
	}
	if (number < 0 && flags->flag & (1 << F_ZERO)
		&& flags->zero_pad_precision > 0)
		flags->precision++;
	
	//printf("%d, %d, %d, %d\n", flags->width, flags->precision, flags->num_length, flags->padding);
	/*
	if (flags->flag & (1 << F_ZERO))
	{
		if (flags->flag & (1 << F_PRECISION) && flags->width > flags->precision)
		{
			if (flags->precision < flags->num_length)
				flags->precision = flags->num_length;
			flags->zero_pad_precision = flags->width - flags->precision;
			if (number < 0)
			{
				flags->num_length++;
				flags->precision++;
			}
		}
		if (number < 0 && flags->flag & (1 << F_PRECISION) && flags->width < flags->precision && flags->width < flags->num_length)
			flags->precision++;
		flags->precision = ft_max(flags->width, flags->precision);
		flags->padding += flags->zero_pad_precision;
		flags->num_length -= flags->zero_pad_precision;
		if (number < 0 && flags->zero_pad_precision > 0)
			flags->precision++;
	}*/
}

static int	get_base(char format)
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
	get_number_length(flags, number);
	//printf("%d, %d, %d, %d\n", flags->width, flags->precision, flags->num_length, flags->padding);
	check_for_zero_flag_base(flags, number);
	itoa_base_printf(number, flags, base);
}
