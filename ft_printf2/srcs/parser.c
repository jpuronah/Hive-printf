/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 13:43:56 by jpuronah          #+#    #+#             */
/*   Updated: 2022/07/01 14:44:18 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	parse_h_l(const char *restrict format, int index, t_printf *flags)
{
	//printf("PARSE_H_L:     index: |%c|\n", format[index]);
	//printf("parse_h_l: %c\n", format[index]);
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
	{
		//printf("flag short/long found: %d\n", flags->flag);
	}
	return (index);
}

int	parse_width_and_precision(const char *restrict format, int index, t_printf *flags)
{
	//printf("PARSE_WIDTH_AND_PRECISION:     index: |%c|\n", format[index]);
	if (ft_isdigit(format[index]) == 1 && format[index] != '0')
	{
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
	if (format[index] == '.')
	{
		//printf("ala wprec: %c\n", format[index]);
		if (ft_atoi(ft_strsub(format, index + 1, 10)))
			flags->precision = ft_atoi(ft_strsub(format, index + 1, 10));
		//printf("precision: %d\n", flags->precision);
		while (ft_isdigit(format[index + 1]) == 1)
			index++;
		index++;
	}
	//printf("ala wprec: %c\n", format[index]);
	return (index);
}

int	parse_flags(const char *restrict format, int index, t_printf *flags)
{
	int		tmp;

	//printf("PARSE_FLAGS:     index: |%c|\n", format[index]);
	//printf(" INDEX  ***BEFORE*** parse_flags: %d\n", index);
	tmp = ft_strchri("# +-0*", format[index], 0);
	while (tmp > -1)
	{
		flags->flag |= (1 << tmp);
		tmp = ft_strchri("# +-0*", format[++index], 0);
	}
	if (flags->flag & (1 << F_ZERO))
		index++;
	/*
	if (flags->flag & (1 << F_PREFIX))
		printf("macro def flag found: |%c|\n", format[index]);
	if (flags->flag & (1 << F_SPACE))
		printf("macro def flag found: |%c|\n", format[index]);
	if (flags->flag & (1 << F_PLUS))
		printf("macro def flag found: |%c|\n", format[index]);
	if (flags->flag & (1 << F_MINUS))
		printf("macro def flag found: |%c|\n", format[index]);
	if (flags->flag & (1 << F_ZERO))
		index++;
	if (flags->flag & (1 << F_ASTERISK))
		printf("macro def flag found: |%c|\n", format[index]);
	*/
	return (index);
}
