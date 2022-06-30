/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:30:54 by jpuronah          #+#    #+#             */
/*   Updated: 2022/06/30 13:56:48 by jpuronah         ###   ########.fr       */
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
	if (!s)
		print_null_string(flags);
	flags->wordlen = ft_strlen(s);
	//check_and_print_flags(flags);

	//!!!!!!
	(p->f & F_APP_PRECI) ? len = MIN(p->precision, len) : 0;
		p->padding = (p->min_length - len) > 0 ? (p->min_length - len) : 0;
	padding();
	while (s[index])
		flags->total_length += write(1, &s[index++], 1);
	padding();
	//va_end(flags->args);
}*/

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
