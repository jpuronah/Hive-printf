/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 13:43:56 by jpuronah          #+#    #+#             */
/*   Updated: 2022/07/26 11:52:57 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

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

int	conversion_specifiers(char *format, int index, t_printf *flags)
{
	index = check_unsigned_and_l(format, index, flags);
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
