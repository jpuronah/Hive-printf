/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 14:36:13 by jpuronah          #+#    #+#             */
/*   Updated: 2022/06/30 12:18:02 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static void	free_flags(t_printf *flags)
{
	if (flags)
	{
		free(flags);
		flags = NULL;
	}
}

void	print_error(char *reason, t_printf *flags)
{
	ft_putendl(reason);
	free_flags(flags);
	exit(1);
}

static t_printf	*init_and_malloc_flags(void)
{
	t_printf	*flags;

	flags = NULL;
	flags = (t_printf *)malloc(sizeof(t_printf));
	if (flags == NULL)
		return (NULL);
	flags->flag = 0;
	flags->total_length = 0;
	flags->number = 0;
	flags->wordlen = 0;
	return (flags);
}

void	check_and_print_flags(t_printf *flags)
{
	while (flags->number-- - flags->wordlen > 0)
		write(1, " ", 1);
}

static int	conversion_specifiers(const char *restrict format, int index, t_printf *flags)
{
	if (format[index] == 'c')
		ft_print_char(flags);
	if (format[index] == 's')
		ft_print_string(flags);
	if (format[index] == 'd' || format[index] == 'i' || format[index] == 'D')
		ft_print_integer(flags);
	check_and_print_flags(flags);
	return (0);
}

int	ft_strchri(const char *s, int c, int index)
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

int	parse_flags(const char *restrict format, int index, t_printf *flags)
{
	int		num_len;
	int		tmp;

	tmp = ft_strchri("# +-0*", format[index + 1], 0);
	printf("%d\n", tmp);
	while (tmp > -1)
	{
		flags->flag |= (1 << tmp);
		tmp = ft_strchri("# +-0*", format[++index + 1], 0);
		printf("%d\n", tmp);
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
	if (ft_isdigit(format[index + 1]) == 1)
		printf("ifdigit: %d\n", format[index]);
	num_len = 1;
	index++;
	while (ft_isdigit(format[index++ + 1]) == 1)
	{
		
	}
		
		num_len++;
	flags->number = ft_atoi(ft_strsub(format, index - num_len, num_len));
	num_len++;
	return (num_len);
}

int	evaluate_format_type(const char *restrict format, int index, t_printf *flags)
{
	char	next;
	char	next_plus_flags;

	next = format[index + 1];
	index += parse_flags(format, index, flags);
	next_plus_flags = format[index];
	if (ft_strchr("csdi", next_plus_flags))// "cspdiouxXfnh%"
		index += conversion_specifiers(format, index, flags);
	return (index);
}

int	ft_printf(const char *restrict format, ...)
{
	t_printf	*flags;
	int			return_value;
	int			index;

	flags = NULL;
	//ft_bzero(flags, sizeof(flags)); tarvii bitwise_memsetin
	flags = init_and_malloc_flags();
	index = 0;
	return_value = 0;
	va_start(flags->args, format);
	while (format[index] != '\0')
	{
		if (format[index] == '%')
			index = evaluate_format_type(format, index, flags);
		else
			return_value += write(1, &format[index], 1);
		index++;
	}
	va_end(flags->args);
	return_value +=flags->total_length;
	free_flags(flags);
	return (return_value);
}
