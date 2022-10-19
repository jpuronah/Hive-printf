/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:30:54 by jpuronah          #+#    #+#             */
/*   Updated: 2022/10/18 10:28:33 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_print_char(t_printf *vars, char ch)
{
	int		c;

	if (ch == '%')
		c = ch;
	else
		c = va_arg(vars->args, int);
	vars->charlen = 1;
	vars->padding = vars->width - vars->charlen;
	if (vars->padding < 0)
		vars->padding = 0;
	padding(vars, 0);
	if (vars->charlen == 1)
		vars->length_written += write(1, &c, 1);
	padding(vars, 1);
}

static void	print_null_string(char *string, t_printf *vars)
{
	if (!string)
	{
		vars->wordlen = 6;
		if (vars->flag & (1 << PRECISION))
			vars->wordlen = ft_min(vars->wordlen, vars->precision);
		if ((vars->width - vars->wordlen) > 0)
			vars->padding = vars->width - vars->wordlen;
		if (vars->padding < 0)
			vars->padding = 0;
		padding(vars, 0);
		printf_write(vars, "(null)", (size_t)vars->wordlen);
		padding(vars, 1);
	}
	else
		vars->length_written += (int)write(1, string,
				(size_t)ft_strlen(string));
}

void	ft_print_string(t_printf *vars)
{
	unsigned char	*string;

	if (~vars->flag & (1 << PRECISION))
		vars->precision -= 1;
	string = va_arg(vars->args, unsigned char *);
	if (!string)
		print_null_string((char *)string, vars);
	else
	{
		vars->wordlen = (int)ft_strlen((char *)string);
		if (vars->flag & (1 << PRECISION))
			vars->wordlen = ft_min(vars->wordlen, vars->precision);
		if ((vars->width - vars->wordlen) > 0)
			vars->padding = (vars->width - vars->wordlen);
		padding(vars, 0);
		printf_write(vars, string, (size_t)vars->wordlen);
		padding(vars, 1);
	}
}
