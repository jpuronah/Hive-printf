/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding_and_pfwrite.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 10:43:34 by jpuronah          #+#    #+#             */
/*   Updated: 2022/10/18 10:43:40 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	printf_write(t_printf *vars, void *output, size_t size)
{
	size_t	original_size;
	int		index;
	char	*string;
	char	tmp;

	index = 0;
	tmp = 0;
	original_size = size;
	string = ft_strdup((char *)output);
	while (size--)
	{
		if (ft_islower(string[index]) == 1 && vars->flag & (1 << CAPS_ON))
		{
			tmp = string[index++] - 32;
			write(1, &tmp, 1);
		}
		else
			write(1, &string[index++], 1);
	}
	vars->length_written += original_size;
	vars->precision = 1;
	free(string);
}

static char	set_padding_character(t_printf *vars)
{
	char	ch;

	ch = 32;
	if (vars->flag & (1 << ZERO))
		ch = 48;
	if (vars->zero_pad_precision > 0)
	{
		ch = 32;
	}
	if (vars->flag & (1 << ZERO) && vars->num_type & (1 << UNSIGNED)
		&& vars->flag & (1 << PRECISION) && vars->precision == 0)
		ch = 32;
	return (ch);
}

void	padding_float(t_printf *vars)
{
	char	ch;

	ch = set_padding_character(vars);
	if (vars->padding > -1)
	{
		while (vars->padding > 0)
		{
			vars->length_written += write(1, &ch, 1);
			vars->padding--;
		}
	}
}

void	padding(t_printf *vars, int phase)
{
	char	ch;

	ch = set_padding_character(vars);
	if (vars->padding > -1)
	{
		if (!phase && !(vars->flag & (1 << MINUS)))
		{
			while (vars->padding > 0)
			{
				vars->length_written += write(1, &ch, 1);
				vars->padding--;
			}
		}
		else if (phase && (vars->flag & (1 << MINUS)))
		{
			while (vars->padding > 0)
			{
				write(1, &ch, 1);
				vars->length_written++;
				vars->padding--;
			}
		}
	}
}
