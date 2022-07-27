/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 11:49:00 by jpuronah          #+#    #+#             */
/*   Updated: 2022/07/26 11:57:24 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

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

int	check_unsigned_and_l(char *format, int index, t_printf *flags)
{
	if (ft_isupper(format[index]) == 1)
		flags->flag |= (1 << F_CAPS_ON);
	if (format[index] == 'u' || format[index] == 'U')
		flags->num_type |= (1 << F_UNSIGNED);
	if (format[index] == 'L')
	{
		flags->flag |= (1 << F_LONG);
		index++;
	}
	return (index);
}
