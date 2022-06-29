/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:50:11 by jpuronah          #+#    #+#             */
/*   Updated: 2022/06/27 18:03:35 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	ft_print_float_or_double(t_printf *flags)
{
	//printf("print_float\n");
	//char	*s;
	double	d_num;
	//float	f_num;
	char	*char_num;
	int		index;

	index = 0;
	d_num = va_arg(flags->args, double);
	char_num = ft_itoa_double(d_num, flags);
	while (char_num[index])
		flags->total_length += write(1, &char_num[index++], 1);
}

void	ft_print_integer(t_printf *flags)
{
	//printf("print_integer\n");
	//char	*s;
	int		integer;
	char	*charteger;
	int		index;

	index = 0;
	integer = va_arg(flags->args, int);
	charteger = ft_itoa(integer);
	while (charteger[index])
		flags->total_length += write(1, &charteger[index++], 1);
	va_end(flags->args);
}

void	ft_print_char(t_printf *flags)
{
	//printf("print_char\n");
	int		c;

	c = va_arg(flags->args, int);
	flags->total_length += write(1, &c, 1);
	va_end(flags->args);
}

void	ft_print_percent(t_printf *flags, char percent)
{
	flags->total_length += write(1, &percent, 1);
	//va_end(flags->args);
}

void	ft_print_string(t_printf *flags)
{
	char	*s;
	int		index;

	index = 0;
	s = va_arg(flags->args, char *);
	while (s[index])
		flags->total_length += write(1, &s[index++], 1);
	//va_end(flags->args);
}
