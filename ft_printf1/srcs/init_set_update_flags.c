/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_set_update_flags.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:36:38 by jpuronah          #+#    #+#             */
/*   Updated: 2022/06/28 13:53:23 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

t_printf	*init_printf_flags(t_printf *flags)
{
	flags = (t_printf *)malloc(sizeof(t_printf));
	if (flags == NULL)
		return (NULL);
	flags->left_pad = 0;
	flags->right_pad = 0;
	flags->width = 0;
	flags->precision = 0;
	flags->zero_padding = 0;
	flags->point = 0;
	flags->dash = 0;
	flags->total_length = 0;
	flags->sign = 0;
	flags->is_zero = 0;
	flags->percentage = 0;
	flags->space_flag = 0;
	return (flags);
}

void	ft_update_flags(t_printf *flags, const char *restrict format, int index)
{
	int	len;

	len = 0;
	if (flags->precision > 0)
	{
		if (ft_isdigit(format[index]) == 1)
		{
			len++;
			flags->precision = format[index] - 48;
		}
	}
}

void	set_flags(const char *format, int index, t_printf *flags)
{
	if (ft_isdigit(format[index]) == 1)
		flags->left_pad = ft_atoi(&format[index]);
	if (format[index] == '.')
		flags->precision = 1;
	if (format[index] == '-')
		flags->dash = 1;
	if (format[index] == '0')
		flags->is_zero = 1;
	if (format[index] == '%')
		flags->percentage = 1;
	//space_flag, total_length, width, sign,, precision padding uupuu
		index++;
}
