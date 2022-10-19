/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 14:36:13 by jpuronah          #+#    #+#             */
/*   Updated: 2022/10/18 11:05:38 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static t_printf	*init_and_malloc_vars(void)
{
	t_printf	*vars;

	vars = NULL;
	vars = (t_printf *)malloc(sizeof(t_printf));
	if (vars == NULL)
		return (NULL);
	vars->format_string = NULL;
	vars->flag = 0;
	vars->num_type = 0;
	vars->num_length = 0;
	vars->numchar = 0;
	vars->length_written = 0;
	vars->width = 0;
	vars->field_width = 0;
	vars->precision = 1;
	vars->padding = 0;
	vars->wordlen = 0;
	vars->charlen = 0;
	vars->min_length = 0;
	vars->zero_pad_precision = 0;
	vars->negative_float = 0;
	vars->padding_char = 32;
	vars->float_sign_written = 0;
	return (vars);
}

static int	conversion_specifiers(char *format, int index, t_printf *vars)
{
	if (format[index] == 's')
		ft_print_string(vars);
	else if (format[index] == 'c' || format[index] == 'C')
		ft_print_char(vars, 0);
	else if (ft_strchri("diD", format[index], 0) > -1)
		get_va_arg(vars);
	else if (format[index] == 'f' || format[index] == 'F')
		get_va_arg_float_double(vars);
	else if (ft_strchri("oOuUxX", format[index], 0) > -1)
		get_va_arg_base(format[index], vars);
	else if (format[index] == 'p')
		print_pointer_address(vars);
	else if (format[index] == '%')
		ft_print_char(vars, '%');
	else if (ft_strchri("# +-0hl", format[index], 0) > 0)
	{
		parse_flags(format, index, vars);
		index++;
		index = conversion_specifiers(format, index, vars);
	}
	else
		printf_write(vars, "", 0);
	return (index);
}

static int	check_caps_unsigned_long(char *format, int index, t_printf *vars)
{
	if (ft_isupper(format[index]) == 1)
		vars->flag |= (1 << CAPS_ON);
	if (format[index] == 'u' || format[index] == 'U')
		vars->num_type |= (1 << UNSIGNED);
	if (format[index] == 'L')
	{
		vars->flag |= (1 << LONG);
		index++;
	}
	return (index);
}

static int	parse_format(char *format, int index, t_printf *vars)
{
	if (format[index] == '%')
		index++;
	index = parse_flags(format, index, vars);
	index = parse_width(format, index, vars);
	index = parse_precision(format, index, vars);
	index = parse_h(format, index, vars);
	index = parse_l(format, index, vars);
	index = check_caps_unsigned_long(format, index, vars);
	index = conversion_specifiers(format, index, vars);
	reset_vars(vars);
	return (index);
}

int	ft_printf(const char *format, ...)
{
	t_printf	*vars;
	int			return_value;
	int			index;

	index = 0;
	vars = NULL;
	vars = init_and_malloc_vars();
	vars->format_string = ft_strdup((char *)format);
	va_start(vars->args, format);
	while (vars->format_string[index] != '\0')
	{
		if (vars->format_string[index] == '%')
		{
			if (!vars->format_string[index + 1])
				break ;
			index = parse_format(vars->format_string, index, vars);
		}
		else
			vars->length_written += write(1, &vars->format_string[index], 1);
		index++;
	}
	va_end(vars->args);
	return_value = vars->length_written;
	free_vars(vars);
	return (return_value);
}
