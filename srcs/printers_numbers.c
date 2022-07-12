/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers_numbers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:45:34 by jpuronah          #+#    #+#             */
/*   Updated: 2022/07/12 20:58:48 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static void	check_flags_and_padding_base(intmax_t number, t_printf *flags, int variable, int base)
{
	if (flags->flag & (1 << F_ZERO))
		flags->precision = flags->width;
	variable = 0;
	if (!(flags->num_length >= flags->precision))
		variable = 1;
	flags->num_length = ft_max(flags->precision, flags->num_length);
	if (flags->flag & (1 << F_PREFIX) && base == 8 && variable == 0)
		flags->width--;
	if (flags->flag & (1 << F_PREFIX) && base == 8 && number == 0 && flags->flag & (1 << F_PRECISION))
		flags->num_length++;
	if (flags->num_length < flags->width)
		flags->padding = flags->width - flags->num_length;
	if (flags->flag & (1 << F_PREFIX) && base == 16 && !(flags->flag & (1 << F_ZERO)))
	{
		flags->padding = ft_max(0, (flags->width - flags->num_length));
		if (flags->flag & (1 << F_PREFIX))
			flags->padding -= 2;
	}
	//printf("padding: %d, precision: %d, width: %d, numlen: %d\n", flags->padding, flags->precision, flags->width, flags->num_length);
}

void	itoa_base_printf(intmax_t number, t_printf *flags, int base)
{
	char		number_as_char[21];
	intmax_t	tmp;
	int			variable;

	variable = 0;
	flags->num_length = 0;
	tmp = number;
	if (number < 0)
		tmp = (uintmax_t)number * -1;
	tmp = ft_abs_ll(number);
	while (tmp)
	{
		tmp /= base;
		flags->num_length++;
	}
	check_flags_and_padding_base(number, flags, variable, base);
	padding(flags, 0);
	tmp = ft_abs_ll(number);
	if ((number || flags->flag & (1 << F_POINTER)) && (flags->flag & (1 << F_PREFIX) && ((base == 8 && variable == 0) || base == 16)))
		printf_write(flags, "0", 1);
	if ((number || flags->flag & (1 << F_POINTER)) && (flags->flag & (1 << F_PREFIX) && base == 16))
	{
		if (flags->flag & (1 << F_CAPS_ON))
			printf_write(flags, "X", 1);
		else
			printf_write(flags, "x", 1);
	}
	itoa_base_fill(tmp, base, number_as_char, flags);
	printf_write(flags, number_as_char, flags->num_length);
	padding(flags, 1);
}

void	parse_va_arg_type_numbers_base(int base, t_printf *flags)
{
	intmax_t	number;

	if (flags->num_type & (1 << F_LONG))
		number = (intmax_t)va_arg(flags->args, unsigned long);
	else if (flags->num_type & (1 << F_LONGLONG))
		number = (intmax_t)va_arg(flags->args, unsigned long long);
	else if (flags->num_type & (1 << F_SHORT))
		number = (intmax_t)((short)va_arg(flags->args, int));
	else if (flags->num_type & (1 << F_SHORTCHAR))
		number = (intmax_t)((char)va_arg(flags->args, int));
	else if (flags->num_type & (1 << F_MAXINT))
		number = (va_arg(flags->args, intmax_t));
	else if (flags->num_type & (1 << F_SIZET))
		number = ((uintmax_t)va_arg(flags->args, size_t));
	else
		number = ((uintmax_t)va_arg(flags->args, unsigned int));
	if (flags->flag & (1 << F_ZERO))
		flags->precision = flags->width;
	itoa_base_printf(number, flags, base);
}

void	parse_va_arg_type_numbers(t_printf *flags)
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
		flags->precision = flags->width;
	itoa_printf(number, flags, 0);
}

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
}
