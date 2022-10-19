/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 13:43:56 by jpuronah          #+#    #+#             */
/*   Updated: 2022/10/18 10:59:51 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	parse_flags(char *format, int index, t_printf *vars)
{
	int		tmp;

	tmp = -1;
	tmp = ft_strchri("# +-0", format[index], 0);
	while (tmp > -1)
	{
		vars->flag |= (1 << tmp);
		if (tmp > -1)
			index++;
		tmp = ft_strchri("# +-0", format[index], 0);
	}
	if (vars->flag & (1 << MINUS))
		vars->flag &= ~(1 << ZERO);
	return (index);
}

int	parse_width(char *format, int index, t_printf *vars)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strsub(format, (unsigned int)index, 10);
	if (ft_isdigit(format[index]) == 1 && format[index] != '0')
	{
		if (ft_atoi(tmp) > 0)
			vars->field_width = (int)ft_atoi(tmp);
		while (ft_isdigit(format[index]) == 1)
			index++;
	}
	vars->width = vars->field_width;
	free(tmp);
	tmp = NULL;
	return (index);
}

int	parse_precision(char *format, int index, t_printf *vars)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strsub(format, (unsigned int)index + 1, 10);
	if (format[index] == '.')
	{
		vars->flag |= (1 << PRECISION);
		if (ft_isdigit(format[index]) == 0)
			vars->precision = 0;
		if (ft_atoi(tmp) > 0)
			vars->precision = (int)ft_atoi(tmp);
		while (ft_isdigit(format[index + 1]) == 1)
			index++;
		index++;
	}
	free(tmp);
	tmp = NULL;
	return (index);
}

int	parse_h(char *format, int index, t_printf *vars)
{
	while (1)
	{
		if (format[index] == 'h')
		{
			if (format[index + 1] == 'h')
				vars->num_type = (1 << SHORTCHAR);
			else
				vars->num_type = (1 << SHORT);
			if (vars->num_type == (1 << SHORTCHAR))
				index++;
			index++;
			break ;
		}
		else
			break ;
	}
	return (index);
}

int	parse_l(char *format, int index, t_printf *vars)
{
	while (1)
	{
		if (format[index] == 'l')
		{
			if (format[index + 1] == 'l')
				vars->num_type |= (1 << LONGLONG);
			else
				vars->num_type |= (1 << LONG);
			if (vars->num_type == (1 << LONGLONG))
				index++;
			index++;
			break ;
		}
		else
			break ;
	}
	return (index);
}
