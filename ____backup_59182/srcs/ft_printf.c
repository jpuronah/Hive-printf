/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 14:36:13 by jpuronah          #+#    #+#             */
/*   Updated: 2022/07/07 11:52:56 by jpuronah         ###   ########.fr       */
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

/*
void	print_error(char *reason, t_printf *flags)
{
	ft_putendl(reason);
	free_flags(flags);
	exit(1);
}*/

static t_printf	*init_and_malloc_structure(void)
{
	t_printf	*flags;

	flags = NULL;
	flags = (t_printf *)malloc(sizeof(t_printf));
	if (flags == NULL)
		return (NULL);
	flags->flag = 0;
	flags->num_type = 0;
	flags->total_length = 0;
	flags->length = 0;
	flags->precision = 0;
	flags->padding = 0;
	flags->number = 0;
	flags->wordlen = 0;
	flags->charlen = 0;
	flags->caps_on = 0;
	return (flags);
}

static int	conversion_specifiers(const char *restrict format, int index, t_printf *flags)
{
	//"cspdiouxXfnh%"
	//printf("CONVERSION_SPECIFIER:     index: |%c|\n", format[index]);
	if (format[index] == 's')
		ft_print_string(flags);	//'°ÅÄ¶' etc char ---->  ft_put_weird_string ?
	else if (format[index] == 'c' || format[index] == 'C')
		ft_print_char(flags, 0);
	else if (ft_strchr("diD", format[index]))// (format[index] == 'd' || format[index] == 'i' || format[index] == 'D'))
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
		ft_print_hexa(flags, format[index]);
	}
	else if (format[index] == 'o')// || format[index] == 'O')
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
		//printf("     INDEX  ***BEFORE*** width_precision: %d\n", index);
	index = parse_width_and_precision(format, index, flags);
		//printf("     INDEX  ***AFTER*** width_precision: %d\n", index);
		//printf("     INDEX  ***BEFORE*** parse_h_l: %d\n", index);
	index = parse_h_l(format, index, flags);
		//printf("     INDEX  ***AFTER*** parse_h_l: %d\n", index);
	index = conversion_specifiers(format, index, flags);
	return (index);
}

int	ft_printf(const char *restrict format, ...)
{
	t_printf	*flags;
	int			return_value;
	int			index;

	flags = NULL;
	//ft_bzero(flags, sizeof(flags)); tarvii bitwise_memsetin
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
	return_value += flags->total_length;
	free_flags(flags);
	return (return_value);
}
