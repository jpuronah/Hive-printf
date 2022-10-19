/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 18:35:18 by jpuronah          #+#    #+#             */
/*   Updated: 2022/10/17 13:46:04 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*malloc_number_as_char(int size)
{
	char	*number_as_char;

	number_as_char = NULL;
	number_as_char = ft_memalloc((size_t)size);
	if (number_as_char == NULL)
		return (NULL);
	return (number_as_char);
}

void	free_number_as_char(char *number_as_char)
{
	free(number_as_char);
	number_as_char = NULL;
}

void	get_number_length(t_printf *vars, intmax_t number)
{
	intmax_t	tmp;

	tmp = number;
	if (tmp > 0)
	{
		while (tmp > 0)
		{
			tmp /= 10;
			vars->num_length++;
		}
	}
	else if (tmp < 0)
	{
		while (tmp < 0)
		{
			tmp /= 10;
			vars->num_length++;
		}
	}
}

void	free_vars(t_printf *vars)
{
	if (vars)
	{
		if (vars->format_string)
		{
			free(vars->format_string);
			vars->format_string = NULL;
		}
		free(vars);
		vars = NULL;
	}
}

void	reset_vars(t_printf *vars)
{
	vars->flag = 0;
	vars->num_type = 0;
	vars->min_length = 0;
	vars->num_length = 0;
	vars->numchar = 0;
	vars->width = 0;
	vars->field_width = 0;
	vars->precision = 1;
	vars->padding = 0;
	vars->zero_pad_precision = 0;
	vars->wordlen = 0;
	vars->charlen = 0;
	vars->negative_float = 0;
	vars->padding_char = 32;
	vars->float_sign_written = 0;
}
