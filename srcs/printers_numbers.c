/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers_numbers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:45:34 by jpuronah          #+#    #+#             */
/*   Updated: 2022/07/12 14:04:37 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static void	check_flags_and_padding_diD(intmax_t number, int length, t_printf *flags)
{
	//printf("padding: %d, precision: %d, width: %d\n", flags->padding, flags->precision, flags->width);
	if ((number < 0 || flags->flag & (1 << F_PLUS) || flags->flag & (1 << F_SPACE)) && flags->flag & (1 << F_ZERO))
		--flags->precision;
	flags->num_length = ft_max(length, flags->precision);
	if (number < 0 || flags->flag & (1 << F_PLUS) || flags->flag & (1 << F_SPACE))
		flags->num_length++;
	if (flags->num_length < flags->width)
		flags->padding = flags->width - flags->num_length;
}

void	itoa_printf(intmax_t number, t_printf *flags, int length)
{
	char		number_as_char[21];
	intmax_t	tmp;

	tmp = number;
	if (number < 0)
		tmp = (uintmax_t)number * -1;
	tmp = ft_abs_ll(number);
	while (tmp)
	{
		tmp /= 10;
		++length;
	}
	check_flags_and_padding_diD(number, length, flags);
	padding(flags, 0);
	tmp = ft_abs_ll(number);
	itoa_base_fill(tmp, 10, number_as_char, flags);
	if (flags->flag & (1 << F_SPACE))
		number_as_char[0] = ' ';
	if (number < 0)
		number_as_char[0] = '-';
	if (number >= 0 && flags->flag & (1 << F_PLUS))
		number_as_char[0] = '+';
	printf_write(flags, number_as_char, flags->num_length);
	padding(flags, 1);
}

void	itoa_base_fill(uintmax_t tmp, int base, char s[21], t_printf *flags)
{
	int		len;

	//printf("numlen: %d, ", flags->num_length);
	//printf("%d\n", flags->flag);
	
	if (tmp && !(flags->flag & (1 << F_POINTER)) && (flags->flag & (1 << F_ZERO)) && (flags->flag & (1 << F_PREFIX)) &&
	base == 16 && !(flags->flag & (1 << F_LONGLONG)) && flags->num_length > 3)
	{
		//printf("paska\n");
		flags->num_length -= 2;
	}
	//if (flags->flag & (1 << F_PREFIX) && base == 16 && ~flags->flag & (1 << F_POINTER))
	//	flags->num_length -= 2;
	len = flags->num_length;
	flags->numchar = 'a' - 10;
	if (flags->caps_on == 1)
		flags->numchar = 'a' - 10 - 32;
	while (len--)
	{
		s[len] = (tmp % base + ((tmp % (uintmax_t)base < 10) ? '0' : flags->numchar));
		tmp /= base;
	}
	(flags->flag & (1 << F_PRECISION) && flags->flag & (1 << F_ZERO)) ? s[0] = ' ' : 0;
}
