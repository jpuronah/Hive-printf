/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:45:34 by jpuronah          #+#    #+#             */
/*   Updated: 2022/08/01 16:22:47 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

void	itoa_base_fill(uintmax_t tmp, int base,
char *number_as_char, t_printf *flags)
{
	int		len;

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
			number_as_char[len] = (char)(tmp % (uintmax_t)base + '0');
		else
			number_as_char[len]
				= (char)(tmp % (uintmax_t)base + (uintmax_t)flags->numchar);
		tmp /= (uintmax_t)base;
	}
}

static void	adjust_padding(intmax_t number, int length, t_printf *flags)
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
		flags->num_length -= flags->zero_pad_precision;
	if (number < 0 && flags->flag & (1 << F_ZERO))
		if (flags->min_length < flags->num_length)
			flags->num_length--;
	if (flags->width > flags->num_length)
		if (flags->precision < flags->num_length)
			flags->precision = ft_max(flags->precision, flags->num_length);
}

static void	add_prefix_character(t_printf *flags,
	intmax_t number, char *number_as_char)
{
	if (flags->flag & (1 << F_SPACE))
		number_as_char[0] = ' ';
	if (number < 0)
		number_as_char[0] = '-';
	if (number >= 0 && flags->flag & (1 << F_PLUS))
		number_as_char[0] = '+';
}

/*printf("padding: %d, prec: %d, wdth: %d, numlen: %d\n", 
		flags->padding, flags->precision, flags->width, flags->num_length);
*/

void	itoa_printf(intmax_t number, t_printf *flags, int length)
{
	char		*number_as_char;
	uintmax_t	tmp;

	number_as_char = NULL;
	tmp = (uintmax_t)ft_abs_long_long((long long)number);
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
	adjust_padding(number, length, flags);
	number_as_char = ft_memalloc((size_t)(flags->num_length + 1));
	padding(flags, 0);
	tmp = (uintmax_t)ft_abs_long_long((long long)number);
	itoa_base_fill(tmp, 10, number_as_char, flags);
	add_prefix_character(flags, number, number_as_char);
	printf_write(flags, number_as_char, (size_t)flags->num_length);
	padding(flags, 1);
	free(number_as_char);
	number_as_char = NULL;
}
