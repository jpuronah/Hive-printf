/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 14:36:13 by jpuronah          #+#    #+#             */
/*   Updated: 2022/07/14 11:52:35 by jpuronah         ###   ########.fr       */
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
	//flags->pad_overflow = 0;
	return (flags);
}

void	printf_write(t_printf *flags, void *new, size_t size)
{
	int		index;
	size_t	hold_size;
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

void		ft_no_conversion_specifier(t_printf *flags, const char *format)
{
	//printf("assa%s\n", format);
	if ((flags->padding = flags->width - 1) > 0)
	{
		padding(flags, 0);
		printf_write(flags, (char *)format, 1);
		padding(flags, 1);
		return ;
	}
	printf_write(flags, (char *)format, 1);
}

static int	conversion_specifiers(const char *format, int index, t_printf *flags)
{
//	printf("c: |%c|\n", format[index]);
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
	else if (ft_strchri("diD", format[index], 0) > -1)
	{
		//printf(":: %c\n", format[index]);
		//printf("pasasksssksaksa\n");
		parse_va_arg_type_numbers(flags);
	}
	else if (format[index] == 'f' || format[index] == 'F')
		(flags->flag & (1 << F_PRECISION) && !flags->precision) ? parse_va_arg_type_numbers(flags) : parse_va_arg_type_numbers_float_double(flags);
	else if (ft_strchri("oOuUbBxX", format[index], 0) > -1)
		parse_va_arg_type_numbers_base(ft_strchri_lu(".b..ou..x", format[index], 0) << 1, flags);
	else if (format[index] == 'p')
		print_pointer_address(flags);
	else if (format[index] == '%')
	{
		//printf("pasaskksa12122ksa\n");
		ft_print_char(flags, '%');
	}
	else
	{
		//printf("pasaskksak98898989sa\n");
		ft_no_conversion_specifier(flags, format);
		index++;
	}
	return (index);
}

static int	evaluate_format_type(const char *format, int index, t_printf *flags)
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

int	ft_printf(const char *format, ...)
{
	t_printf	*flags;
	char		*format_string;
	int			return_value;
	int			index;

	flags = NULL;
	flags = init_and_malloc_structure();
	index = 0;
	return_value = 0;
	format_string = ft_strdup((char *)format);
	va_start(flags->args, format);
	while (format_string[index] != '\0')
	{
		//printf("loopc: |%c|\n", format_string[index]);
		if (format_string[index] == '%')
		{
			if (!format_string[index + 1])
				break ;
			index = evaluate_format_type(format_string, index, flags);
		}
		else
		{
			return_value += write(1, &format_string[index], 1);
		}
		index++;
	}
	va_end(flags->args);
	return_value += flags->length_written;
	free(format_string);
	free_flags(flags);
	return (return_value);
}
