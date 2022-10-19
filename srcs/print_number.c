/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:45:34 by jpuronah          #+#    #+#             */
/*   Updated: 2022/10/17 19:56:58 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	itoa_base_fill(uintmax_t tmp, int base,
char *number_as_char, t_printf *vars)
{
	int		len;

	if (tmp && !(vars->flag & (1 << POINTER))
		&& (vars->flag & (1 << ZERO))
		&& (vars->flag & (1 << PREFIX)) && base == 16
		&& !(vars->flag & (1 << LONGLONG))
		&& vars->num_length > 3)
		vars->num_length -= 2;
	len = vars->num_length;
	vars->numchar = 'a' - 10;
	if (vars->flag & (1 << CAPS_ON))
		vars->numchar = 'a' - 10 - 32;
	while (len--)
	{
		if (tmp % (uintmax_t)base < 10)
		{
			number_as_char[len] = (char)(tmp % (uintmax_t)base + '0');
		}
		else
		{
			number_as_char[len]
				= (char)(tmp % (uintmax_t)base + (uintmax_t)vars->numchar);
		}
		tmp /= (uintmax_t)base;
	}
}

static void	adjust_padding(intmax_t number, int length, t_printf *vars)
{
	if (vars->flag & (1 << ZERO) && vars->width > vars->precision)
		vars->padding = vars->width - vars->precision;
	if (vars->flag & (1 << ZERO) && number < 0)
	{
		vars->precision++;
		vars->padding--;
	}
	if ((number < 0 || vars->flag & (1 << PLUS)
			|| vars->flag & (1 << SPACE)) && vars->flag & (1 << ZERO))
		--vars->precision;
	vars->num_length = ft_max(length, vars->precision);
	if (number < 0 || vars->flag & (1 << PLUS)
		|| vars->flag & (1 << SPACE))
		vars->num_length++;
	if (vars->num_length < vars->width)
		vars->padding = vars->width - vars->num_length;
	if (vars->flag & (1 << ZERO) && vars->zero_pad_precision > 0)
		vars->num_length -= vars->zero_pad_precision;
	if (number < 0 && vars->flag & (1 << ZERO))
		if (vars->min_length < vars->num_length)
			vars->num_length--;
	if (vars->width > vars->num_length)
		if (vars->precision < vars->num_length)
			vars->precision = ft_max(vars->precision, vars->num_length);
}

static void	add_prefix_character(t_printf *vars,
	intmax_t number, char *number_as_char)
{
	if (vars->flag & (1 << SPACE))
		number_as_char[0] = ' ';
	if (number < 0)
		number_as_char[0] = '-';
	if (number >= 0 && vars->flag & (1 << PLUS))
		number_as_char[0] = '+';
}

void	itoa_printf(intmax_t number, t_printf *vars, int length)
{
	char		*number_as_char;
	uintmax_t	tmp;

	number_as_char = NULL;
	tmp = (uintmax_t)ft_abs_long_long((long long)number);
	if (tmp == 0 && vars->flag & (1 << ZERO))
		length++;
	while (tmp)
	{
		tmp /= 10;
		++length;
	}
	vars->min_length = length;
	if (number < 0)
		vars->min_length++;
	adjust_padding(number, length, vars);
	number_as_char = ft_memalloc((size_t)(vars->num_length + 1));
	padding(vars, 0);
	tmp = (uintmax_t)ft_abs_long_long((long long)number);
	itoa_base_fill(tmp, 10, number_as_char, vars);
	add_prefix_character(vars, number, number_as_char);
	printf_write(vars, number_as_char, (size_t)vars->num_length);
	padding(vars, 1);
	free(number_as_char);
	number_as_char = NULL;
}
