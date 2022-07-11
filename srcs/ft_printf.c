/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 14:36:13 by jpuronah          #+#    #+#             */
/*   Updated: 2022/07/11 19:37:21 by jpuronah         ###   ########.fr       */
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
	//flags->number = 0;
	flags->wordlen = 0;
	flags->charlen = 0;
	flags->caps_on = 0;
	flags->pad_overflow = 0;
	return (flags);
}

void	printf_write(t_printf *flags, void *new, size_t size)
{
	////printf("|%s|\n", (char *)new);
	write(1, new, size);
	flags->length_written += size;
	
	/*while (21 - buffer_index < (int)size)
	{
		diff = 21 - buffer_index;
		ft_memcpy(&(dst[buffer_index]), &(new[new_i]), diff);
		size -= diff;
		new_i += diff;
		buffer_index += diff;
		write(1, dst, buffer_index);
		flags->length_written += buffer_index;
		buffer_index = 0;
	}
	//printf("DEST\n\n|%s|\n|%s|\n", dst, (char *)new);
	ft_memcpy(&(dst[buffer_index]), &(new[new_i]), diff);
	buffer_index += size;*/
	flags->precision = 1;
}

/*void	printf_write(t_printf *flags, void *new, size_t size)
{
	int			diff;
	long long	new_i;
	int			buffer_index;
	char		dst[21];

	new_i = 0;
	buffer_index = 0;
	while (21 - buffer_index < (int)size)
	{
		diff = 21 - buffer_index;
		ft_memcpy(&(dst[buffer_index]), &(new[new_i]), diff);
		size -= diff;
		new_i += diff;
		buffer_index += diff;
		write(1, dst, buffer_index);
		flags->length_written += buffer_index;
		buffer_index = 0;
	}
	//printf("DEST\n\n|%s|\n|%s|\n", dst, (char *)new);
	ft_memcpy(&(dst[buffer_index]), &(new[new_i]), diff);
	buffer_index += size;
}*/

void	itoa_base_fill(uintmax_t tmp, int base, char s[21], t_printf *flags)
{
	int		len;

	//if (tmp && !(flags->flag & F_POINTER) && (flags->flag & F_ZERO) && (flags->flag & F_PREFIX) &&
	//base == 16 && !(flags->flag & F_LONGLONG) && flags->num_length > 3)
	//	flags->num_length -= 2;
	len = flags->num_length;
	flags->numchar = 'a' - 10 - 0;
	while (len--)
	{
		/*printf("%ju\n", tmp);
		printf("%ju\n", tmp % base);
		printf("%ju\n", tmp % base + '0');*/
		//s[len] = (char *)((tmp % base + ((tmp % base < 10))) ? '0' : flags->numchar);//tmp % base + '0';
		s[len] = (char)(tmp % base + ((tmp % (uintmax_t)base < 10) ? '0' : flags->numchar));
		/*printf("d: %d\n", s[len]);
		printf("c: %c\n", s[len]);*/
		//if (tmp % base >= 10)
		//	s[len] += 32;
		////printf("tmp : %ju\n", tmp);
		////printf("p->pc : %d\n", flags->numchar);
		////printf("base : %d\n", base);
		////printf("s len : %c\n\n", s[len]);
		tmp /= base;
	}
	(flags->flag & (1 << F_PRECISION) && flags->flag & (1 << F_ZERO)) ? s[0] = ' ' : 0;
}

void	check_flags_and_padding(intmax_t number, int length, t_printf *flags)
{
	if ((number < 0 || flags->flag & (1 << F_PLUS) || flags->flag & (1 << F_SPACE)) && flags->flag & (1 << F_ZERO))
		--flags->precision;
	flags->num_length = ft_max(length, flags->precision);
	if (number < 0 || flags->flag & (1 << F_PLUS) || flags->flag & (1 << F_SPACE))
		flags->num_length++;
	if (flags->num_length < flags->width)
		flags->padding = flags->width - flags->num_length;
	//printf("padding: %d\n", flags->padding);
}

void	itoa_printf(intmax_t number, t_printf *flags, int length)
{
	char		number_as_char[21];
	intmax_t	tmp;

	tmp = number;
	if (number < 0)
		tmp = (uintmax_t)number * -1;
	tmp = ft_abs(number);
	while (tmp)
	{
		tmp /= 10;
		++length;
	}
	//printf("padding: %d, width %d, precision %d, wordlen %d, overf: %d\n", flags->padding, flags->width, flags->precision, flags->wordlen, flags->pad_overflow);
	check_flags_and_padding(number, length, flags);
	padding(flags, 0);
	tmp = ft_abs_ll(number);
	itoa_base_fill(tmp, 10, number_as_char, flags);
	if (flags->flag & (1 << F_SPACE))
		number_as_char[0] = ' ';
	//flags->flag & (1 << F_SPACE) ? number_as_char[0] = ' ' : 0;
	//(number < 0) ? number_as_char[0] = '-' : 0;
	if (number < 0)
		number_as_char[0] = '-';
	//(flags->flag & (1 << F_PLUS) && number >= 0) ? number_as_char[0] = '+' : 0;
	if (number >= 0 && flags->flag & (1 << F_PLUS))
		number_as_char[0] = '+';
	printf_write(flags, number_as_char, flags->num_length);
	padding(flags, 1);
}

void	parse_va_arg_type(t_printf *flags)
{
	intmax_t	number;

	if (flags->num_type & (1 << F_LONG))
		number = (intmax_t)va_arg(flags->args, long);
	else if (flags->num_type & (1 << F_LONGLONG))
		number = (intmax_t)va_arg(flags->args, long long);
	else if (flags->num_type & (1 << F_SHORT))
	{
		number = (intmax_t)((short)va_arg(flags->args, int));
	}
	else if (flags->num_type & (1 << F_SHORTCHAR))
	{
		number = (intmax_t)((char)va_arg(flags->args, int));
	}
	else if (flags->num_type & (1 << F_MAXINT))
		number = (va_arg(flags->args, intmax_t));
	else if (flags->num_type & F_UNSIGNED)
		number = ((intmax_t)va_arg(flags->args, ssize_t));
	else
		number = ((intmax_t)va_arg(flags->args, int));
	if (flags->flag & (1 << F_ZERO))
		flags->precision = flags->width;
	//printf("parse: %d\n", flags->precision);
	//printf("parse: %d\n", flags->num_length);
	itoa_printf(number, flags, 0);
}

static int	conversion_specifiers(const char *restrict format, int index, t_printf *flags)
{
	if (format[index] == 's')
	{
		if (~flags->flag & (1 << F_PRECISION))
			flags->precision -= 1;
		ft_print_string(flags);
	}
	else if (format[index] == 'c' || format[index] == 'C')
		ft_print_char(flags, 0);
	else if (ft_strchr("diD", format[index]))
	{
		parse_va_arg_type(flags);
		/*if (flags->num_type & (1 << F_LONG) || flags->num_type & (1 << F_LONGLONG))
			ft_print_long_long(flags);
		else
			ft_print_integer(flags);*/
	}
	else if (format[index] == 'u')
		ft_print_unsigned(flags);
	else if (format[index] == 'f')
		ft_print_float_double(flags);
	else if (format[index] == 'x' || format[index] == 'X')
	{
		if (flags->num_type & (1 << F_LONG) || flags->num_type & (1 << F_LONGLONG))
			ft_print_hexa_long(flags, format[index]);
		else
			ft_print_hexa(flags, format[index]);
	}
	else if (format[index] == 'o')
		ft_print_octal(flags);
	else if (format[index] == '%')
		ft_print_char(flags, '%');
	return (index);
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
