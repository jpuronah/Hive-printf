/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 14:36:13 by jpuronah          #+#    #+#             */
/*   Updated: 2022/08/02 14:04:25 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

static t_printf	*init_and_malloc_structure(void)
{
	t_printf	*flags;

	flags = NULL;
	flags = (t_printf *)malloc(sizeof(t_printf));
	if (flags == NULL)
		return (NULL);
	flags->format_string = NULL;
	flags->flag = 0;
	flags->num_type = 0;
	flags->num_length = 0;
	flags->numchar = 0;
	flags->length_written = 0;
	flags->width = 0;
	flags->precision = 1;
	flags->padding = 0;
	flags->wordlen = 0;
	flags->charlen = 0;
	flags->min_length = 0;
	flags->zero_pad_precision = 0;
	return (flags);
}

static int	conversion_specifiers(char *format, int index, t_printf *flags)
{
	if (format[index] == 's')
		ft_print_string(flags);
	else if (format[index] == 'c' || format[index] == 'C')
		ft_print_char(flags, 0);
	else if (ft_strchri("diD", format[index], 0) > -1)
		get_va_arg(flags);
	else if (format[index] == 'f' || format[index] == 'F')
		get_va_arg_float_double(flags);
	else if (ft_strchri("oOuUbBxX", format[index], 0) > -1)
		get_va_arg_base(format[index], flags);
	else if (format[index] == 'p')
		print_pointer_address(flags);
	else if (format[index] == '%')
		ft_print_char(flags, '%');
	else if (ft_strchr("# +-0hl", format[index]) > 0)
	{
		parse_flags(format, index, flags);
		index++;
		index = conversion_specifiers(format, index, flags);
	}
	else
		printf_write(flags, "", 0);
	return (index);
}

static int	check_caps_and_unsigned_and_long(char *format, int index, t_printf *flags)
{
	if (ft_isupper(format[index]) == 1)
		flags->flag |= (1 << F_CAPS_ON);
	if (format[index] == 'u' || format[index] == 'U')
		flags->num_type |= (1 << F_UNSIGNED);
	if (format[index] == 'L')
	{
		flags->flag |= (1 << F_LONG);
		index++;
	}
	return (index);
}

static int	evaluate_format_type(char *format, int index, t_printf *flags)
{
	if (format[index] == '%')
		index++;
	index = parse_flags(format, index, flags);
	index = parse_width(format, index, flags);
	index = parse_precision(format, index, flags);
	index = parse_h(format, index, flags);
	index = parse_l(format, index, flags);
	index = check_caps_and_unsigned_and_long(format, index, flags);
	index = conversion_specifiers(format, index, flags);
	reset_flags(flags);
	return (index);
}

int	ft_printf(const char *restrict format, ...)
{
	t_printf	*flags;
	int			return_value;
	int			index;

	index = 0;
	flags = NULL;
	flags = init_and_malloc_structure();
	flags->format_string = ft_strdup((char *)format);
	va_start(flags->args, format);
	while (flags->format_string[index] != '\0')
	{
		if (flags->format_string[index] == '%')
		{
			if (!flags->format_string[index + 1])
				break ;
			index = evaluate_format_type(flags->format_string, index, flags);
		}
		else
			flags->length_written += write(1, &flags->format_string[index], 1);
		index++;
	}
	va_end(flags->args);
	return_value = flags->length_written;
	free_flags(flags);
	return (return_value);
}
