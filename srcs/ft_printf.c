/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 14:36:13 by jpuronah          #+#    #+#             */
/*   Updated: 2022/07/08 13:47:01 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

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
	flags->length_written = 0;
	flags->padding_length = 0;
	flags->width = 0;
	flags->precision = 0;
	flags->padding = 0;
	//flags->number = 0;
	flags->wordlen = 0;
	flags->charlen = 0;
	flags->caps_on = 0;
	flags->pad_overflow = 0;
	return (flags);
}

static int	conversion_specifiers(const char *restrict format, int index, t_printf *flags)
{
	if (format[index] == 's')
		ft_print_string(flags);
	else if (format[index] == 'c' || format[index] == 'C')
		ft_print_char(flags, 0);
	else if (ft_strchr("diD", format[index]))
	{
		if (flags->num_type & (1 << F_LONG) || flags->num_type & (1 << F_LONGLONG))
			ft_print_long_long(flags);
		else
			ft_print_integer(flags);
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
			index = evaluate_format_type(format, index, flags);
		else
			return_value += write(1, &format[index], 1);
		index++;
	}
	va_end(flags->args);
	return_value += flags->length_written;
	free_flags(flags);
	return (return_value);
}
