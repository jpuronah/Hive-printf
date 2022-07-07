/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers_characters.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:30:54 by jpuronah          #+#    #+#             */
/*   Updated: 2022/07/07 13:49:57 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	padding(t_printf *flags, int phase)
{
	char	ch;

	ch = 32;
	if (flags->flag & (1 << F_ZERO))
		ch = 48;
	if (flags->padding > 0)
	{
		if (!phase && !(flags->flag & (1 << F_MINUS)))
		{
			while (flags->padding > 0)
			{
				write(1, &ch, 1);
				flags->total_length++;
				flags->padding--;
			}
		}
		else if (phase && (flags->flag & (1 << F_MINUS)))
		{
			while (flags->padding > 0)
			{
				write(1, &ch, 1);
				flags->total_length++;
				flags->padding--;
			}
		}
	}
}

void	ft_print_char(t_printf *flags, char ch)
{
	int		c;

	if (ch == '%')
		c = ch;
	else
		c = va_arg(flags->args, int);
	flags->charlen = 1;
	flags->padding = flags->length - flags->charlen;
	if (flags->padding < 0)
		flags->padding = 0;
	padding(flags, 0);
	if (flags->charlen == 1)
		flags->total_length += write(1, &c, 1);
	padding(flags, 1);
}

void	print_null_string(char *string, t_printf *flags)
{
	if (!string)
	{
		if (!(flags->flag & (1 << F_ZERO)))
			flags->total_length += write(1, "(null)", 6);
		else
			while (flags->length--)
				flags->total_length += write(1, "0", 1);
	}
	else
		flags->total_length += write(1, string, (int)ft_strlen(string));
}

void	ft_print_string(t_printf *flags)
{
	char	*string;
	int		index;

	index = 0;
	string = va_arg(flags->args, char *);
	if (!string)
		print_null_string(string, flags);
	else
	{
		flags->wordlen = ft_strlen(string);
		if ((flags->wordlen - flags->precision) > 0)
			flags->padding = (flags->length) - (flags->wordlen - flags->precision);
		else
			flags->padding = flags->length;
		padding(flags, 0);
		if (flags->precision > 0)
			while (string[index] && flags->precision--)
				flags->total_length += write(1, &string[index++], 1);
		
		else
			while (string[index])
				flags->total_length += write(1, &string[index++], 1);
		padding(flags, 1);
	}
}
