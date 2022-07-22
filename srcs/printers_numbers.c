/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers_numbers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:45:34 by jpuronah          #+#    #+#             */
/*   Updated: 2022/07/22 11:57:34 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

void	itoa_base_fill(uintmax_t tmp, int base, char s[21], t_printf *flags)
{
	int		len;

	//printf("wid: %d, prec: %d, numlen: %d\n", flags->width, flags->precision, flags->num_length);
	if (tmp && !(flags->flag & (1 << F_POINTER))
		&& (flags->flag & (1 << F_ZERO))
		&& (flags->flag & (1 << F_PREFIX)) && base == 16
		&& !(flags->flag & (1 << F_LONGLONG))
		&& flags->num_length > 3)
		flags->num_length -= 2;
	len = flags->num_length;
	flags->numchar = 'a' - 10;
	if (flags->flag & (1 << F_CAPS_ON))
		flags->numchar = 'a' - 10 - 32;
	while (len--)
	{
		if (tmp % (uintmax_t)base < 10)
			s[len] = (char)(tmp % (uintmax_t)base + '0');
		else
			s[len] = (char)(tmp % (uintmax_t)base + (uintmax_t)flags->numchar);
		tmp /= (uintmax_t)base;
	}
	//if (flags->flag & (1 << F_PRECISION) && flags->flag & (1 << F_ZERO))// && flags->width < flags->precision)
	//	s[0] = ' ';


	//printf("|%ju|\n", tmp);
	//printf("wid: %d, prec: %d, numlen: %d\n", flags->width, flags->precision, flags->num_length);
	//printf("string: %s\n", s);
	//if (tmp == 0)
	//	s[0] = '0';
}

static void	base_adjust_padding(uintmax_t number,
	t_printf *flags, int oct_zero_check, int base)
{
	//if (flags->flag & (1 << F_ZERO))
	//	flags->precision = flags->width;
	if (flags->flag & (1 << F_ZERO) && flags->width > flags->precision)
		flags->padding = flags->width - flags->precision;
	if (flags->flag & (1 << F_ZERO) && number < 0)
	{
		flags->precision++;
		flags->padding--;
	}
	flags->num_length = ft_max(flags->precision, flags->num_length);
	if (flags->flag & (1 << F_PREFIX) && base == 8 && oct_zero_check == 0)
		flags->width--;
	if (flags->flag & (1 << F_PREFIX) && base == 8 && number == 0
		&& flags->flag & (1 << F_PRECISION))
		flags->num_length++;
	if (flags->num_length < flags->width)
		flags->padding = flags->width - flags->num_length;
	if (flags->flag & (1 << F_PREFIX) && base == 16
		&& !(flags->flag & (1 << F_ZERO)))
	{
		flags->padding = ft_max(0, (flags->width - flags->num_length));
		if (flags->flag & (1 << F_PREFIX))
			flags->padding -= 2;
	}
}

void	itoa_base_printf(uintmax_t number, t_printf *flags, int base)
{
	uintmax_t	tmp;
	int			oct_zero_check;
	char		number_as_char[210];//this not ok

	oct_zero_check = 0;
	flags->num_length = 0;
	tmp = number;
	while (tmp)
	{
		tmp /= (uintmax_t)base;
		flags->num_length++;
	}
	if (flags->num_length < flags->precision)
		oct_zero_check = 1;
	base_adjust_padding(number, flags, oct_zero_check, base);
	padding(flags, 0);
	if ((number || flags->flag & (1 << F_POINTER))
		&& (flags->flag & (1 << F_PREFIX)
			&& ((base == 8 && oct_zero_check == 0) || base == 16)))
		printf_write(flags, "0", 1);
	if ((number || (flags->flag & (1 << F_POINTER)))
		&& (flags->flag & (1 << F_PREFIX) && base == 16))
	{
		if (flags->flag & (1 << F_CAPS_ON))
			printf_write(flags, "X", 1);
		else
			printf_write(flags, "x", 1);
	}
	itoa_base_fill(number, base, number_as_char, flags);
	printf_write(flags, number_as_char, (size_t)flags->num_length);
	padding(flags, 1);
}

static void	int_adjust_padding(intmax_t number, int length, t_printf *flags)
{
	if (flags->flag & (1 << F_ZERO) && flags->width > flags->precision)
		flags->padding = flags->width - flags->precision;
	if (flags->flag & (1 << F_ZERO) && number < 0)
	{
		flags->precision++;
		flags->padding--;
	}
	if ((number < 0 || flags->flag & (1 << F_PLUS)
			|| flags->flag & (1 << F_SPACE)) && flags->flag & (1 << F_ZERO))
		--flags->precision;
	flags->num_length = ft_max(length, flags->precision);
	if (number < 0 || flags->flag & (1 << F_PLUS)
		|| flags->flag & (1 << F_SPACE))
		flags->num_length++;
	if (flags->num_length < flags->width)
		flags->padding = flags->width - flags->num_length;
	if (flags->flag & (1 << F_ZERO))
		flags->num_length -= flags->zero_padding_precision;
}

void	itoa_printf(intmax_t number, t_printf *flags, int length)
{
	char		number_as_char[210];//this not ok
	uintmax_t	tmp;

	//printf("padding: %d, prec: %d, wdth: %d, numlen: %d\n", flags->padding, flags->precision, flags->width, flags->num_length);
	tmp = (uintmax_t)ft_abs_ll((long long)number);
	if (tmp == 0 && flags->flag & (1 << F_ZERO))
		length++;
	while (tmp)
	{
		tmp /= 10;
		++length;
	}
	flags->min_length = length;
	if (number < 0)
		flags->min_length++;
	int_adjust_padding(number, length, flags);
	padding(flags, 0);
	tmp = (uintmax_t)ft_abs_ll((long long)number);
	if (number < 0 && flags->flag & (1 << F_ZERO))
		if (flags->min_length < flags->num_length)
			flags->num_length--;
	itoa_base_fill(tmp, 10, number_as_char, flags);
	if (flags->flag & (1 << F_SPACE))
		number_as_char[0] = ' ';
	if (number < 0)
		number_as_char[0] = '-';
	if (number >= 0 && flags->flag & (1 << F_PLUS))
		number_as_char[0] = '+';
	printf_write(flags, number_as_char, (size_t)flags->num_length);
	padding(flags, 1);
}
