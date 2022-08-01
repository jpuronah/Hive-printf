/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 13:43:56 by jpuronah          #+#    #+#             */
/*   Updated: 2022/08/01 16:23:16 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

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
