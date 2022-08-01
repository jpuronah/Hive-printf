/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_and_no_specifier.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:30:54 by jpuronah          #+#    #+#             */
/*   Updated: 2022/08/01 16:44:34 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

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

	nul_str = "(null)";
	if (!string)
	{
		flags->wordlen = 6;
		if (flags->flag & (1 << F_PRECISION))
			flags->wordlen = ft_min(flags->wordlen, flags->precision);
		if ((flags->width - flags->wordlen) > 0)
			flags->padding = flags->width - flags->wordlen;
		if (flags->padding < 0)
			flags->padding = 0;
		padding(flags, 0);
		printf_write(flags, nul_str, (size_t)flags->wordlen);
		padding(flags, 1);
	}
	else
		flags->length_written += (int)write(1, string,
				(size_t)ft_strlen(string));
}

void	ft_print_string(t_printf *flags)
{
	unsigned char	*string;

	if (~flags->flag & (1 << F_PRECISION))
		flags->precision -= 1;
	string = va_arg(flags->args, unsigned char *);
	if (!string)
		print_null_string((char *)string, flags);
	else
	{
		flags->wordlen = (int)ft_strlen((char *)string);
		if (flags->flag & (1 << F_PRECISION))
			flags->wordlen = ft_min(flags->wordlen, flags->precision);
		if ((flags->width - flags->wordlen) > 0)
			flags->padding = (flags->width - flags->wordlen);
		padding(flags, 0);
		printf_write(flags, string, (size_t)flags->wordlen);
		padding(flags, 1);
	}
}
