/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:30:54 by jpuronah          #+#    #+#             */
/*   Updated: 2022/06/28 15:57:05 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	ft_print_char(t_printf *flags)
{
	int		c;

	c = va_arg(flags->args, int);
	flags->wordlen = 1;
	check_and_print_flags(flags);
	flags->total_length += write(1, &c, 1);
	//va_end(flags->args);
}

void	ft_print_string(t_printf *flags)
{
	char	*s;
	int		index;

	index = 0;
	s = va_arg(flags->args, char *);
	flags->wordlen = ft_strlen(s);
	check_and_print_flags(flags);
	while (s[index])
		flags->total_length += write(1, &s[index++], 1);
	//va_end(flags->args);
}

void	ft_print_integer(t_printf *flags)
{
	int		integer;
	char	*charteger;
	int		index;

	index = 0;
	integer = va_arg(flags->args, int);
	charteger = ft_itoa(integer);
	flags->wordlen = ft_strlen(charteger);
	check_and_print_flags(flags);
	while (charteger[index])
		flags->total_length += write(1, &charteger[index++], 1);
	//va_end(flags->args);
}
