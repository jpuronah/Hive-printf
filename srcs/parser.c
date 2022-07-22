/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 13:43:56 by jpuronah          #+#    #+#             */
/*   Updated: 2022/07/22 12:44:49 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

/*int	parse_h_l(char *format, int index, t_printf *flags)
{
	while (1)
	{
		if (format[index] == 'l')
		{
			if (format[index + 1] == 'l')
				flags->num_type |= (1 << F_LONGLONG);
			else
				flags->num_type |= (1 << F_LONG);
			if (flags->num_type == (1 << F_LONGLONG))
				index++;
			index++;
			break ;
		}
		else if (format[index] == 'h')
		{
			if (format[index + 1] == 'h')
				flags->num_type = (1 << F_SHORTCHAR);
			else
				flags->num_type = (1 << F_SHORT);
			if (flags->num_type == (1 << F_SHORTCHAR))
				index++;
			index++;
			break ;
		}
		else
			break ;
		index++;
	}
	return (index);
}*/

int	parse_h(char *format, int index, t_printf *flags)
{
	while (1)
	{
		if (format[index] == 'h')
		{
			if (format[index + 1] == 'h')
				flags->num_type = (1 << F_SHORTCHAR);
			else
				flags->num_type = (1 << F_SHORT);
			if (flags->num_type == (1 << F_SHORTCHAR))
				index++;
			index++;
			break ;
		}
		else
			break ;
		index++;
	}
	return (index);
}

int	parse_l(char *format, int index, t_printf *flags)
{
	while (1)
	{
		if (format[index] == 'l')
		{
			if (format[index + 1] == 'l')
				flags->num_type |= (1 << F_LONGLONG);
			else
				flags->num_type |= (1 << F_LONG);
			if (flags->num_type == (1 << F_LONGLONG))
				index++;
			index++;
			break ;
		}
		else
			break ;
		index++;
	}
	return (index);
}

int	parse_width(char *format, int index, t_printf *flags)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strsub(format, (unsigned int)index, 10);
	if (ft_isdigit(format[index]) == 1 && format[index] != '0')
	{
		if (ft_atoi(tmp) > 0)
			flags->width = (int)ft_atoi(tmp);
		while (ft_isdigit(format[index]) == 1)
			index++;
	}
	free(tmp);
	tmp = NULL;
	return (index);
}

int	parse_precision(char *format, int index, t_printf *flags)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strsub(format, (unsigned int)index + 1, 10);
	if (format[index] == '.')
	{
		flags->flag |= (1 << F_PRECISION);
		if (ft_isdigit(format[index]) == 0)
			flags->precision = 0;
		if (ft_atoi(tmp) > 0)
			flags->precision = (int)ft_atoi(tmp);
		while (ft_isdigit(format[index + 1]) == 1)
			index++;
		index++;
	}
	free(tmp);
	tmp = NULL;
	return (index);
}

int	parse_flags(char *format, int index, t_printf *flags)
{
	int		tmp;

	tmp = -1;
	tmp = ft_strchri("# +-0", format[index], 0);
	while (tmp > -1)
	{
		flags->flag |= (1 << tmp);
		if (tmp > -1)
			index++;
		tmp = ft_strchri("# +-0", format[index], 0);
	}
	if (flags->flag & (1 << F_MINUS))
		flags->flag &= ~(1 << F_ZERO);
	return (index);
}

static int	check_cs(char *format, int index, t_printf *flags)
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

int	conversion_specifiers(char *format, int index, t_printf *flags)
{
	index = check_cs(format, index, flags);
	if (format[index] == 's')
		ft_print_string(flags);
	else if (format[index] == 'c' || format[index] == 'C')
		ft_print_char(flags, 0);
	else if (ft_strchri("diD", format[index], 0) > -1)
		get_va_arg(flags);
	else if (format[index] == 'f' || format[index] == 'F')
	{
		if (flags->flag & (1 << F_PRECISION) && !flags->precision)
			get_va_arg(flags);
		else
			get_va_arg_float_double(flags);
	}
	else if (ft_strchri("oOuUbBxX", format[index], 0) > -1)
		get_va_arg_base(format[index], flags);
	else if (format[index] == 'p')
		print_pointer_address(flags);
	else if (format[index] == '%')
		ft_print_char(flags, '%');
	else
		ft_no_conversion_specifier(flags, format);
	return (index);
}
