/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 13:43:56 by jpuronah          #+#    #+#             */
/*   Updated: 2022/07/27 14:39:38 by jpuronah         ###   ########.fr       */
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
