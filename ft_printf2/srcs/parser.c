/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 13:43:56 by jpuronah          #+#    #+#             */
/*   Updated: 2022/06/30 16:21:30 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static int	ft_strchri(const char *s, int c, int index)
{
	char	*str;
	char	ch;

	str = (char *)s;
	ch = (char)c;
	while (str[index] != '\0')
	{
		if (str[index] == ch)
			return (index);
		index++;
	}
	return (-1);
}

int	parse_h_l(const char *restrict format, int index, t_printf *flags)
{
	while (1)
	{
		if (format[index] == 'l')
		{
			if (format[index + 1] == 'l')
				flags->flag |= (1 << F_LONGLONG);
			else
				flags->flag |= (1 << F_LONG);
		}
		else if (format[index] == 'h')
		{
			if (format[index + 1] == 'h')
				flags->flag = (1 << F_SHORTSHORT);
			else
				flags->flag = (1 << F_SHORT);
		}
		else
			break ;
		index++;
	}
	if (flags->flag & (1 << F_SHORT) || flags->flag & (1 << F_SHORTSHORT) || flags->flag & (1 << F_LONG) || flags->flag & (1 << F_LONGLONG))
		printf("flag short/long found: %d\n", flags->flag);
	return (index);
}

int	parse_width_and_precision(const char *restrict format, int index, t_printf *flags)
{
	//printf("wprec: %c\n", format[index]);
	if (ft_isdigit(format[index + 1]) == 1 && format[index + 1] != '0')
	{
		index++;
		//printf("ylä wprec: %c\n", format[index]);
		if (ft_atoi(ft_strsub(format, index, 10)) > 0)
			flags->length = ft_atoi(ft_strsub(format, index, 10));
		//printf("flags->length found: %d\n", flags->length);
		while (ft_isdigit(format[index]) == 1)
		{
			index++;
			//printf("loopylä wprec: %c\n", format[index]);
		}
	}
	if (format[index + 1] == '.')
	{
		//printf("al wprec: %c\n", format[index]);
		if (ft_atoi(ft_strsub(format, index + 1, 10)) > 0)
			flags->precision = ft_atoi(ft_strsub(format, index + 1, 10));
		//printf("flags->precision found: %d\n", flags->precision);
		while (ft_isdigit(format[index + 1]) == 1)
			index++;
	}
	//printf("ala wprec: %c\n", format[index]);
	return (index);
}

int	parse_flags(const char *restrict format, int index, t_printf *flags)
{
	int		tmp;

	//printf(" INDEX  ***BEFORE*** parse_flags: %d\n", index);
	tmp = ft_strchri("# +-0*", format[index + 1], 0);
	while (tmp > -1)
	{
		flags->flag |= (1 << tmp);
		tmp = ft_strchri("# +-0*", format[++index + 1], 0);
	}
	if (flags->flag & (1 << F_PREFIX))
		printf("macro def flag found: |%c|\n", format[index]);
	if (flags->flag & (1 << F_SPACE))
		printf("macro def flag found: |%c|\n", format[index]);
	if (flags->flag & (1 << F_PLUS))
		printf("macro def flag found: |%c|\n", format[index]);
	if (flags->flag & (1 << F_MINUS))
		printf("macro def flag found: |%c|\n", format[index]);
	if (flags->flag & (1 << F_ZERO))
		printf("macro def flag found: |%c|\n", format[index]);
	if (flags->flag & (1 << F_ASTERISK))
		printf("macro def flag found: |%c|\n", format[index]);
	return (index);
}
