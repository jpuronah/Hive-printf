/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_number_base.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 14:30:50 by jpuronah          #+#    #+#             */
/*   Updated: 2022/10/18 10:28:56 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	base_adjust_padding_2(uintmax_t number, t_printf *vars)
{
	if (vars->flag & (1 << ZERO) && vars->flag & (1 << PRECISION)
		&& vars->width > vars->precision)
		vars->padding = vars->width - vars->precision;
	if (vars->flag & (1 << ZERO) && number < 0)
	{
		vars->precision++;
		vars->padding--;
	}
	vars->num_length = ft_max(vars->precision, vars->num_length);
}

static void	base_adjust_padding(uintmax_t number, t_printf *vars, int base)
{
	base_adjust_padding_2(number, vars);
	if (base == 8 && vars->flag & (1 << PREFIX) && number != 0)
		vars->width--;
	if (vars->flag & (1 << PREFIX) && base == 8 && number == 0
		&& vars->flag & (1 << PRECISION))
		vars->num_length++;
	if (vars->num_length < vars->width)
		vars->padding = vars->width - vars->num_length;
	if (vars->flag & (1 << PREFIX) && base == 16)
	{
		vars->padding = ft_max(0, (vars->width - vars->num_length));
		if (vars->flag & (1 << PREFIX))
			vars->padding -= 2;
	}
}

static void	prefix(uintmax_t number, t_printf *vars,
int base, int octal_precision)
{
	if ((number || vars->flag & (1 << POINTER))
		&& (vars->flag & (1 << PREFIX)
			&& ((base == 8 && octal_precision == 0) || base == 16)))
		printf_write(vars, "0", 1);
	if ((number || (vars->flag & (1 << POINTER)))
		&& (vars->flag & (1 << PREFIX) && base == 16))
	{
		if (vars->flag & (1 << CAPS_ON))
			printf_write(vars, "X", 1);
		else
			printf_write(vars, "x", 1);
		if (vars->flag & (1 << POINTER) && vars->flag & (1 << PREFIX)
			&& vars->width <= vars->precision)
			vars->padding -= 2;
	}
}

void	itoa_base_printf(uintmax_t number, t_printf *vars, int base)
{
	uintmax_t	tmp;
	int			octal_precision;
	char		*number_as_char;

	number_as_char = NULL;
	octal_precision = 0;
	vars->num_length = 0;
	tmp = number;
	while (tmp && vars->num_length++ > -1)
		tmp /= (uintmax_t)base;
	if (vars->num_length < vars->precision)
		octal_precision = 1;
	if (vars->flag & (1 << PREFIX) && vars->flag & (1 << ZERO))
		prefix(number, vars, base, octal_precision);
	base_adjust_padding(number, vars, base);
	number_as_char = malloc_number_as_char((vars->num_length + 1));
	if (number_as_char == NULL)
		exit(1);
	padding(vars, 0);
	if (!(vars->flag & (1 << PREFIX)) || !(vars->flag & (1 << ZERO)))
		prefix(number, vars, base, octal_precision);
	itoa_base_fill(number, base, number_as_char, vars);
	printf_write(vars, number_as_char, (size_t)vars->num_length);
	padding(vars, 1);
	free_number_as_char(number_as_char);
}

void	print_pointer_address(t_printf *vars)
{
	void	*pointer;

	pointer = va_arg(vars->args, void *);
	vars->flag |= (1 << PREFIX);
	vars->flag |= (1 << POINTER);
	itoa_base_printf((uintmax_t)pointer, vars, 16);
	vars->flag = 0;
}
