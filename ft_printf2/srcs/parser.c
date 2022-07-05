/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 13:43:56 by jpuronah          #+#    #+#             */
/*   Updated: 2022/07/05 15:54:14 by jpuronah         ###   ########.fr       */
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
			{
				//printf("lonlong\n");
				flags->num_type |= (1 << F_LONGLONG);
			}
			else
				flags->num_type |= (1 << F_LONG);
		}
		else if (format[index] == 'h')
		{
			if (format[index + 1] == 'h')
				flags->num_type = (1 << F_SHORTSHORT);
			else
				flags->num_type = (1 << F_SHORT);
		}
		else
			break ;
		index++;
	}
	//printf("%d, %hd\n", flags->flag, flags->num_type);
	/*if (flags->flag & (1 << F_SHORT) || flags->flag & (1 << F_SHORTSHORT) || flags->flag & (1 << F_LONG) || flags->flag & (1 << F_LONGLONG))
	{
		//printf("flag short/long found: %d\n", flags->flag);
	}*/
	return (index);
}
/*
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
		if (ft_atoi(ft_strsub(format, index + 1, 10)))
			flags->precision = ft_atoi(ft_strsub(format, index + 1, 10));
		//printf("ala wprec: %c\n", format[index]);
		//printf("precision: %d\n", flags->precision);
		while (ft_isdigit(format[index + 1]) == 1)
			index++;
		index++;
	}
	//printf("ala wprec: %c\n", format[index]);
	return (index);
}
*/

int	parse_width_and_precision(const char *restrict format, int index, t_printf *flags)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strsub(format, index, 10);
	//printf("PARSE_WIDTH_AND_PRECISION:     index: |%c|\n", format[index]);
	if (ft_isdigit(format[index]) == 1 && format[index] != '0')
	{
		if (ft_atoi(tmp) > 0)
			flags->length = ft_atoi(tmp);
		while (ft_isdigit(format[index]) == 1)
			index++;
	}
	free(tmp);
	tmp = NULL;
	tmp = ft_strsub(format, index + 1, 10);
	if (format[index] == '.')
	{
		if (ft_atoi(tmp) > 0)
			flags->precision = ft_atoi(tmp);
		while (ft_isdigit(format[index + 1]) == 1)
			index++;
		index++;
	}
	free(tmp);
	tmp = NULL;
//	printf("length: %d\n", flags->length);
//	printf("precision: %d\n", flags->precision);
	return (index);
}

int	parse_flags(const char *restrict format, int index, t_printf *flags)
{
	int		tmp;

	//printf("PARSE_FLAGS:     index: |%c|\n", format[index]);
	//printf(" INDEX  ***BEFORE*** parse_flags: %d\n", index);
//	printf("flags: %c\n", format[index]);
	tmp = ft_strchri("# +-0*", format[index], 0);
	//printf("tmp: %d\n", tmp);
	// Whats the logic here?!?! xdd
	if (tmp > -1)
	{
		flags->flag |= (1 << tmp);
		while (ft_strchr("# +-0*", format[index]) != NULL)
		{
			//printf("flags: |%c|\n", format[index]);
			index++;
		}
	}
	//printf("flag: %d\n", flags->flag);
	/*printf("tmp: %d\n", tmp);
	printf("flag: %d\n", flags->flag);
	printf("%d\n", (1 << F_SPACE));
	printf("%d\n", (1 << F_PLUS));*/
	//index--;
	while (format[index] == '0')//flags->flag & (1 << F_ZERO))
	{
		//printf("if\n");
		index++;
	}
	if (flags->flag & (1 << F_SPACE) && ~flags->flag & (1 << F_PLUS))
		flags->total_length += write(1, " ", 1);
	if (flags->flag & (1 << F_PLUS))
		flags->total_length += write(1, "+", 1);
	/*if (flags->flag & (1 << F_SPACE) && ~flags->flag & (1 << F_PLUS))
		flags->total_length += write(1, " ", 1);
	if (flags->flag & (1 << F_PLUS))
		flags->total_length += write(1, "+", 1);*/
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
