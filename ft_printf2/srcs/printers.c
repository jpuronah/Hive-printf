/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:30:54 by jpuronah          #+#    #+#             */
/*   Updated: 2022/06/30 16:22:08 by jpuronah         ###   ########.fr       */
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

void	print_null_string(char *string, t_printf *flags)
{
	if (!string)
	{
		if (!(flags->flag & (1 << F_ZERO)))
			write(1, "(null)", 6);
		else
			while (flags->length--)
				write(1, "0", 1);
	}
	else
		write(1, string, (int)ft_strlen(string));
}

void	padding(t_printf *flags, int phase)
{
	if (flags->padding > 0)
	{
		if (!phase && !(flags->flag & (1 << F_MINUS)))
		{
			while (flags->padding > 0)
			{
				write(1, " ", 1);
				flags->padding--;
			}
		}
		else if (phase && (flags->flag & (1 << F_MINUS)))
		{
			while (flags->padding > 0)
			{
				write(1, " ", 1);
				flags->padding--;
			}
		}
	}
}

void	ft_print_string(t_printf *flags)
{
	char	*string;
	int		index;

	index = 0;
	string = va_arg(flags->args, char *);
	if (!string)
		print_null_string(string, flags);
	flags->wordlen = ft_strlen(string);
	if ((flags->wordlen - flags->precision) > 0)
		flags->padding = (flags->length - flags->wordlen);
	else
		flags->padding = 0;
	padding(flags, 0);
	while (string[index])
		flags->total_length += write(1, &string[index++], 1);
	padding(flags, 1);
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
