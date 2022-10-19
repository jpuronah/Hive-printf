/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 10:48:02 by jpuronah          #+#    #+#             */
/*   Updated: 2022/10/18 10:17:49 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	fill_float(t_printf *vars, char *number_as_char,
	unsigned long long decimal, unsigned long long whole_number)
{
	int		precision;
	int		whole_length;

	whole_length = ft_number_length((long long)whole_number);
	precision = vars->precision;
	while (precision-- > 0)
	{
		number_as_char[whole_length + precision + 1] = decimal % 10 + 48;
		decimal /= 10;
	}
	if (vars->precision != 0)
		number_as_char[whole_length] = '.';
	if (vars->precision == 0 && vars->flag & (1 << PREFIX))
		number_as_char[whole_length] = '.';
	while (whole_length-- > 0)
	{
		number_as_char[whole_length] = whole_number % 10 + 48;
		whole_number /= 10;
	}
}

static void	write_flags_float(t_printf *vars)
{
	if ((vars->padding_char == 32 || vars->flag & (1 << MINUS))
		&& !vars->float_sign_written)
	{
		if (vars->negative_float == 1)
		{
			vars->length_written += write(1, "-", 1);
			vars->float_sign_written = 1;
		}
		if (vars->flag & (1 << PLUS) && !vars->negative_float)
		{
			vars->length_written += write(1, "+", 1);
			vars->float_sign_written = 1;
			vars->padding--;
		}
		if (vars->flag & (1 << SPACE) && !vars->negative_float)
		{
			vars->length_written += write(1, " ", 1);
			vars->float_sign_written = 1;
			vars->padding--;
		}
	}
}

static void	float_double_toa_logic(t_printf *vars, char *number_as_char)
{
	if (vars->flag & (1 << MINUS))
	{
		write_flags_float(vars);
		printf_write(vars, number_as_char, (size_t)vars->num_length);
	}
	if (~vars->flag & (1 << MINUS) && vars->flag & (1 << ZERO))
	{
		write_flags_float(vars);
		if (vars->flag & (1 << SPACE) || (vars->flag & (1 << PLUS)
				&& ~ vars->flag & (1 << ZERO)))
			vars->padding++;
	}
	padding_float(vars);
	if (~vars->flag & (1 << MINUS))
	{
		write_flags_float(vars);
		printf_write(vars, number_as_char, (size_t)vars->num_length);
	}
}

static void	float_double_toa(t_printf *vars, long double float_number,
	unsigned long long whole_number)
{
	int					precision;
	unsigned long long	decimal;
	char				*number_as_char;

	number_as_char = NULL;
	precision = vars->precision;
	number_as_char = malloc_number_as_char(precision + 1
			+ ft_number_length((long long)whole_number) + 3);
	if (number_as_char == NULL)
		exit(1);
	while (precision-- > 0)
		float_number *= 10;
	vars->num_length = ft_number_length((long long)whole_number)
		+ vars->precision + 1;
	decimal = (unsigned long long)float_number;
	adjust_padding_float(vars);
	fill_float(vars, number_as_char, decimal, whole_number);
	vars->num_length = (int)ft_strlen(number_as_char);
	float_double_toa_logic(vars, number_as_char);
	free_number_as_char(number_as_char);
}

void	get_va_arg_float_double(t_printf *vars)
{
	long double			float_number;
	unsigned long long	whole_number;

	if (~vars->flag & (1 << PRECISION))
		vars->precision = 6;
	if (vars->flag & (1 << LONG))
		float_number = (long double)(va_arg(vars->args, long double));
	else
		float_number = (long double)(va_arg(vars->args, double));
	if (float_number < 0.0 || 1 / float_number == 1 / -0.0)
	{
		vars->negative_float = 1;
		float_number *= -1;
	}
	float_number = round_float(vars, float_number);
	whole_number = (unsigned long long)float_number;
	float_number -= whole_number;
	float_double_toa(vars, float_number, whole_number);
}
