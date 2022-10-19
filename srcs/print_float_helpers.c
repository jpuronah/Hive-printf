/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:44:42 by jpuronah          #+#    #+#             */
/*   Updated: 2022/10/18 11:01:13 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	adjust_padding_float_2(t_printf *vars)
{
	if ((vars->padding_char == 32 || vars->flag & (1 << MINUS))
		&& !vars->float_sign_written)
	{
		if (vars->negative_float == 1)
			vars->padding--;
		if (vars->flag & (1 << PLUS) && !vars->negative_float)
			vars->padding--;
		if (vars->flag & (1 << SPACE) && !vars->negative_float)
			vars->padding--;
	}
}

void	adjust_padding_float(t_printf *vars)
{
	if (vars->flag & (1 << PRECISION) && vars->precision == 0)
		vars->num_length--;
	if (vars->width > vars->precision + 3)
		vars->padding = vars->width - (vars->precision + 3);
	if (vars->flag & (1 << PRECISION) && vars->precision + 3 < vars->width)
		while (vars->padding + 3 < vars->width)
			vars->padding++;
	if (vars->flag & (1 << PRECISION) && vars->precision + 3 < vars->width
		&& vars->precision == 0)
		while (vars->padding + 1 < vars->width)
			vars->padding++;
	if (vars->flag & (1 << PLUS) && !vars->negative_float)
		vars->padding--;
	if (vars->flag & (1 << SPACE) && (~vars->flag & (1 << MINUS))
		&& !vars->negative_float)
		vars->padding++;
	else if (vars->flag & (1 << SPACE) && vars->flag & (1 << MINUS)
		&& vars->flag & (1 << PRECISION) && !vars->negative_float)
		vars->padding++;
	if (vars->flag & (1 << ZERO) && vars->flag & (1 << SPACE)
		&& vars->width <= vars->num_length)
		vars->flag &= ~(1 << ZERO);
	if (~vars->flag & (1 << SPACE))
		vars->padding += vars->width - (vars->num_length + vars->padding);
	adjust_padding_float_2(vars);
}

long double	round_float(t_printf *vars, long double float_number)
{
	int				precision_index;
	int				precision;
	long double		precision_factor;
	long double		tmp_float;

	precision_index = 0;
	precision_factor = 1.0;
	precision = vars->precision;
	if (precision == 0)
	{
		precision = 1;
		precision_factor /= 10;
	}
	while (precision_index++ < precision)
		precision_factor *= 10;
	tmp_float = float_number;
	tmp_float *= precision_factor;
	if ((unsigned long long)tmp_float % 2 == 0 && tmp_float
		- (unsigned long long)tmp_float == 0.5)
		return (float_number);
	else
		return (float_number + 0.5 / precision_factor);
}
