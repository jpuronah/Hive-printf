/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers_characters.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:30:54 by jpuronah          #+#    #+#             */
/*   Updated: 2022/07/19 13:08:15 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

void	padding(t_printf *flags, int phase)
{
	char	ch;

	ch = 32;
	if (flags->flag & (1 << F_ZERO))
		ch = 48;
	if (flags->padding > -1)
	{
		if (!phase && !(flags->flag & (1 << F_MINUS)))
		{
			while (flags->padding > 0)
			{
				flags->length_written += write(1, &ch, 1);
				flags->padding--;
			}
		}
		else if (phase && (flags->flag & (1 << F_MINUS)))
		{
			while (flags->padding > 0)
			{
				write(1, &ch, 1);
				flags->length_written++;
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
	flags->padding = flags->width - flags->charlen;
	if (flags->padding < 0)
		flags->padding = 0;
	padding(flags, 0);
	if (flags->charlen == 1)
		flags->length_written += write(1, &c, 1);
	padding(flags, 1);
}

void	print_null_string(char *string, t_printf *flags)
{
	char	*nul_str;
	int		index;
	int		precision;

	precision = -1;
	if (flags->precision > 0)
		precision = flags->precision;
	nul_str = "(null)";
	index = 0;
	if (!string)
	{
		flags->padding = flags->width - 6;
		if (flags->padding < 0)
			flags->padding = 0;
		padding(flags, 0);
		if (!(flags->flag & (1 << F_ZERO)))
			while (nul_str[index] != '\0' && precision--)
				flags->length_written += write(1, &nul_str[index++], 1);

		padding(flags, 1);
	}
	else
		flags->length_written += (int)write(1, string, (size_t)ft_strlen(string));
}

void	ft_print_string(t_printf *flags)
{
	char	*string;
	int		index;

	index = 0;
	if (~flags->flag & (1 << F_PRECISION))
		flags->precision -= 1;
	string = va_arg(flags->args, char *);
	if (!string)
		print_null_string(string, flags);
	else
	{
		flags->wordlen = (int)ft_strlen(string);
		if (flags->flag & (1 << F_PRECISION))
		{
			flags->wordlen = ft_min(flags->wordlen, flags->precision);
		}
		flags->padding = (flags->width - flags->wordlen);
		if (flags->padding < 0)
			flags->padding = 0;
		else
			padding(flags, 0);
		if (flags->precision == 0)
			flags->precision = -1;
		while (string[index] && flags->precision--)
			flags->length_written += write(1, &string[index++], 1);
		padding(flags, 1);
	}
}
