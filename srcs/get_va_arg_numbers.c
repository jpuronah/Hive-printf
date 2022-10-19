/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_va_arg_numbers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 12:33:45 by jpuronah          #+#    #+#             */
/*   Updated: 2022/10/17 19:57:14 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	check_for_zero_flag(t_printf *vars, intmax_t number)
{
	if (vars->flag & (1 << ZERO))
	{
		if (vars->flag & (1 << PRECISION) && vars->width > vars->precision)
		{
			if (vars->precision < vars->num_length)
				vars->precision = vars->num_length;
			vars->zero_pad_precision = vars->width - vars->precision;
			if (number < 0)
				vars->num_length++;
		}
		if (number < 0 && vars->flag & (1 << PRECISION)
			&& vars->width < vars->precision
			&& vars->width < vars->num_length)
			vars->precision++;
		vars->precision = ft_max(vars->width, vars->precision);
		vars->padding += vars->zero_pad_precision;
		if (vars->zero_pad_precision > 0)
			vars->num_length -= vars->zero_pad_precision;
		if (number < 0 && vars->zero_pad_precision > 0)
			vars->precision++;
	}
}

void	get_va_arg(t_printf *vars)
{
	intmax_t	number;

	if (vars->num_type & (1 << LONG))
		number = (intmax_t)va_arg(vars->args, long);
	else if (vars->num_type & (1 << LONGLONG))
		number = (intmax_t)va_arg(vars->args, long long);
	else if (vars->num_type & (1 << SHORT))
		number = (intmax_t)((short)va_arg(vars->args, int));
	else if (vars->num_type & (1 << SHORTCHAR))
		number = (intmax_t)((char)va_arg(vars->args, int));
	else if (vars->num_type & (1 << MAXINT))
		number = (va_arg(vars->args, intmax_t));
	else if (vars->num_type & UNSIGNED)
		number = ((intmax_t)va_arg(vars->args, ssize_t));
	else
		number = ((intmax_t)va_arg(vars->args, int));
	get_number_length(vars, number);
	check_for_zero_flag(vars, number);
	itoa_printf(number, vars, 0);
}

static void	check_for_zero_flag_base(t_printf *vars, uintmax_t number)
{
	if (vars->flag & (1 << ZERO) && vars->flag & (1 << PRECISION)
		&& vars->precision == 0)
		vars->padding = vars->width - vars->num_length;
	else if (vars->flag & (1 << ZERO))
	{
		if (vars->width > vars->precision && vars->flag & (1 << PRECISION))
			vars->zero_pad_precision = vars->width - vars->precision;
		if (vars->precision == 0)
			vars->precision = ft_max(vars->width, vars->precision);
		vars->padding += vars->zero_pad_precision;
		vars->num_length -= vars->zero_pad_precision;
	}
	if (number < 0 && vars->flag & (1 << ZERO)
		&& vars->zero_pad_precision > 0)
		vars->precision++;
}

static int	get_base(char format)
{
	int	base;

	base = 1;
	if (format == 'o' || format == 'O')
		base = 8;
	if (format == 'u' || format == 'U')
		base = 10;
	if (format == 'x' || format == 'X')
		base = 16;
	return (base);
}

void	get_va_arg_base(char format, t_printf *vars)
{
	uintmax_t	number;
	int			base;

	base = get_base(format);
	if (vars->num_type & (1 << LONG))
		number = ((uintmax_t)va_arg(vars->args, unsigned long));
	else if (vars->num_type & (1 << LONGLONG))
		number = ((uintmax_t)va_arg(vars->args, unsigned long long));
	else if (vars->num_type & (1 << SHORT))
		number = (uintmax_t)((unsigned short)va_arg(vars->args, int));
	else if (vars->num_type & (1 << SHORTCHAR))
		number = (uintmax_t)((unsigned char)va_arg(vars->args, int));
	else if (vars->num_type & (1 << SIZET))
		number = ((uintmax_t)va_arg(vars->args, size_t));
	else
		number = ((uintmax_t)va_arg(vars->args, unsigned int));
	get_number_length(vars, (intmax_t)number);
	check_for_zero_flag_base(vars, number);
	itoa_base_printf(number, vars, base);
}
