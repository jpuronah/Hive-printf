/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_base.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 14:30:50 by jpuronah          #+#    #+#             */
/*   Updated: 2022/10/06 16:31:56 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

static void	base_adjust_padding_2(uintmax_t number, t_printf *flags)
{
	if (flags->flag & (1 << F_ZERO) && flags->flag & (1 << F_PRECISION)
		&& flags->width > flags->precision)
		flags->padding = flags->width - flags->precision;
	if (flags->flag & (1 << F_ZERO) && number < 0)
	{
		flags->precision++;
		flags->padding--;
	}
	flags->num_length = ft_max(flags->precision, flags->num_length);
}

static void	base_adjust_padding(uintmax_t number, t_printf *flags, int base)
{
	base_adjust_padding_2(number, flags);
	if (base == 8 && flags->flag & (1 << F_PREFIX)
		&& ~ flags->flag & (1 << F_PRECISION))
		flags->width--;
	if (flags->flag & (1 << F_PREFIX) && base == 8 && number == 0
		&& flags->flag & (1 << F_PRECISION))
		flags->num_length++;
	if (flags->num_length < flags->width)
		flags->padding = flags->width - flags->num_length;
	if (flags->flag & (1 << F_PREFIX) && base == 16)
	{
		flags->padding = ft_max(0, (flags->width - flags->num_length));
		if (flags->flag & (1 << F_PREFIX))
			flags->padding -= 2;
	}
}

static void	prefix(uintmax_t number, t_printf *flags,
int base, int octal_precision)
{
	if ((number || flags->flag & (1 << F_POINTER))
		&& (flags->flag & (1 << F_PREFIX)
			&& ((base == 8 && octal_precision == 0) || base == 16)))
		printf_write(flags, "0", 1);
	if ((number || (flags->flag & (1 << F_POINTER)))
		&& (flags->flag & (1 << F_PREFIX) && base == 16))
	{
		if (flags->flag & (1 << F_CAPS_ON))
			printf_write(flags, "X", 1);
		else
			printf_write(flags, "x", 1);
	}
}

void	itoa_base_printf(uintmax_t number, t_printf *flags, int base)
{
	uintmax_t	tmp;
	int			octal_precision;
	char		*number_as_char;

	number_as_char = NULL;
	octal_precision = 0;
	flags->num_length = 0;
	tmp = number;
	while (tmp && flags->num_length++ > -1)
		tmp /= (uintmax_t)base;
	if (flags->num_length < flags->precision)
		octal_precision = 1;
	if (flags->flag & (1 << F_PREFIX) && flags->flag & (1 << F_ZERO))
		prefix(number, flags, base, octal_precision);
	base_adjust_padding(number, flags, base);
	number_as_char = ft_memalloc((size_t)(flags->num_length + 1));
	padding(flags, 0);
	if (!(flags->flag & (1 << F_PREFIX)) || !(flags->flag & (1 << F_ZERO)))
		prefix(number, flags, base, octal_precision);
	itoa_base_fill(number, base, number_as_char, flags);
	printf_write(flags, number_as_char, (size_t)flags->num_length);
	padding(flags, 1);
	free(number_as_char);
	number_as_char = NULL;
}

void	print_pointer_address(t_printf *flags)
{
	void	*pointer;

	pointer = va_arg(flags->args, void *);
	flags->flag |= (1 << F_PREFIX);
	flags->flag |= (1 << F_POINTER);
	itoa_base_printf((uintmax_t)pointer, flags, 16);
	flags->flag = 0;
}
