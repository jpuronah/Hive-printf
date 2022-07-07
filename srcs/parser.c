/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 13:43:56 by jpuronah          #+#    #+#             */
/*   Updated: 2022/07/07 21:21:11 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	parse_h_l(const char *restrict format, int index, t_printf *flags)
{
	while (1)
	{
		if (format[index] == 'l')
		{
			if (format[index + 1] == 'l')
			{
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
	return (index);
}

int	parse_width(const char *restrict format, int index, t_printf *flags)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strsub(format, index, 10);
	if (ft_isdigit(format[index]) == 1 && format[index] != '0')
	{
		if (ft_atoi(tmp) > 0)
			flags->width = ft_atoi(tmp);
		while (ft_isdigit(format[index]) == 1)
			index++;
	}
	free(tmp);
	tmp = NULL;
	
	/*tmp = ft_strsub(format, index + 1, 10);
	if (format[index] == '.')
	{
		if (ft_atoi(tmp) > 0)
			flags->precision = ft_atoi(tmp);
		while (ft_isdigit(format[index + 1]) == 1)
			index++;
		index++;
	}
	free(tmp);
	tmp = NULL;*/
	return (index);
}

int	parse_precision(const char *restrict format, int index, t_printf *flags)
{
	char	*tmp;

	/*tmp = NULL;
	tmp = ft_strsub(format, index, 10);
	if (ft_isdigit(format[index]) == 1 && format[index] != '0')
	{
		if (ft_atoi(tmp) > 0)
			flags->padding_length = ft_atoi(tmp);
		while (ft_isdigit(format[index]) == 1)
			index++;
	}
	free(tmp);*/
	tmp = NULL;
	tmp = ft_strsub(format, index + 1, 10);
	if (format[index] == '.')
	{
		flags->flag |= (1 << F_PRECISION);
		if (ft_atoi(tmp) > 0)
			flags->precision = ft_atoi(tmp);
		while (ft_isdigit(format[index + 1]) == 1)
			index++;
		index++;
	}
	free(tmp);
	tmp = NULL;
	//printf("%d, %d\n", flags->width, flags->precision);
	//printf("flag: %d\n", flags->flag);
	return (index);
}

int	parse_flags(const char *restrict format, int index, t_printf *flags)
{
	int		tmp;

	tmp = -1;
	tmp = ft_strchri("# +-0*", format[index], 0);
	while (tmp > -1)
	{
		flags->flag |= (1 << tmp);
		if (tmp > -1)
			index++;
		tmp = ft_strchri("# +-0*", format[index], 0);
	}
	//if (flags->flag & (1 << F_PREFIX) && flags->flag & (1 << F_ZERO))
	//	printf("molempi paska\n");
	//while (format[index] == '0')
	//	index++;
	if (flags->flag & (1 << F_PLUS))
		flags->length_written += write(1, "+", 1);
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
