/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 14:36:13 by jpuronah          #+#    #+#             */
/*   Updated: 2022/07/12 14:35:21 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include <stdarg.h>
#include <errno.h>
#include <stdio.h>

static void	free_flags(t_printf *flags)
{
	if (flags)
	{
		free(flags->format);
		free(flags);
		flags = NULL;
	}
}

static t_printf	*init_and_malloc_structure(void)
{
	t_printf	*flags;

	flags = NULL;
	flags = (t_printf *)malloc(sizeof(t_printf));
	if (flags == NULL)
		return (NULL);
	flags->flag = 0;
	flags->num_type = 0;
	flags->num_length = 0;
	flags->numchar = 0;

	flags->length_written = 0;
	flags->padding_length = 0;
	flags->width = 0;
	flags->precision = 1;
	flags->padding = 0;
	flags->wordlen = 0;
	flags->charlen = 0;
	flags->caps_on = 0;
	flags->pad_overflow = 0;
	return (flags);
}

int	ft_islower(int c)
{
	if ((c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}

void	printf_write(t_printf *flags, void *new, size_t size)
{
	int		index;
	int		hold_size;
	char	*string;
	char	tmp;

	index = 0;
	tmp = 0;
	hold_size = size;
	string = ft_strdup((char *)new);
	while (size--)
	{
		//printf("string: |%s|\n", string);
		//printf("|%c|\n", string[index]);
		if (ft_islower(string[index]) == 1 && flags->flag & (1 << F_CAPS_ON))
		{
			tmp = string[index++] - 32;
			//printf("|%c, %c|\n", tmp, string[index - 1]);
			write(1, &tmp, 1);
		}
		else
			write(1, &string[index++], 1);
	}
	flags->length_written += hold_size;
	flags->precision = 1;
	free(string);
}

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

int	ft_is_capital(int c)
{
	if ((c >= 65 && c <= 90))
		return (1);
	else
		return (0);
}

static int	conversion_specifiers(const char *restrict format, int index, t_printf *flags)
{
	if (ft_is_capital(format[index]) == 1)
		flags->flag |= (1 << F_CAPS_ON);
	if (format[index] == 'u' || format[index] == 'U')
		flags->num_type |= (1 << F_UNSIGNED);
	//if (flags->num_type & (1 << F_LONG) && flags->num_type & (1 << F_UNSIGNED))
	if (format[index] == 's')
	{
		if (~flags->flag & (1 << F_PRECISION))
			flags->precision -= 1;
		ft_print_string(flags);
	}
	else if (format[index] == 'c' || format[index] == 'C')
		ft_print_char(flags, 0);
	else if (ft_strchr("diD", format[index]))
		parse_va_arg_type_numbers(flags);
	else if (ft_strchr("oOuUbBxX", format[index]))
		parse_va_arg_type_numbers_base(ft_strchri_lu(".b..ou..x", format[index], 0) << 1, flags);
	else if (format[index] == '%')
		ft_print_char(flags, '%');
	return (index);
	/*else if (format[index] == 'f' || format[index] == 'F')
		(flags->flag & (1 << F_PRECISION) && !flags->precision) ? parse_va_arg_type_numbers(flags) : pf_putdouble(flags);*/
}

static int	evaluate_format_type(const char *restrict format, int index, t_printf *flags)
{
	if (format[index] == '%')
		index++;
	index = parse_flags(format, index, flags);
	index = parse_width(format, index, flags);
	index = parse_precision(format, index, flags);
	index = parse_h_l(format, index, flags);
	index = conversion_specifiers(format, index, flags);
	return (index);
}

int	ft_printf(const char *restrict format, ...)
{
	t_printf	*flags;
	int			return_value;
	int			index;

	flags = NULL;
	flags = init_and_malloc_structure();
	index = 0;
	return_value = 0;
	va_start(flags->args, format);
	while (format[index] != '\0')
	{
		if (format[index] == '%')
		{
			index = evaluate_format_type(format, index, flags);
		}
		else
		{
			return_value += write(1, &format[index], 1);
		}
		index++;
	}
	va_end(flags->args);
	return_value += flags->length_written;
	free_flags(flags);
	return (return_value);
}
