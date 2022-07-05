/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers_numbers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:45:34 by jpuronah          #+#    #+#             */
/*   Updated: 2022/07/05 17:02:00 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

/* CHARTEGER stuff gotta be gone */

void	ft_print_long_long(t_printf *flags)
{
	long		long_num;
	long long	longlong_num;
	char		*charteger_l;
	char		*charteger_ll;
	int			index;

	charteger_l = NULL;
	charteger_ll = NULL;
	index = 0;
	if (flags->num_type & (1 << F_LONG))
	{
		long_num = va_arg(flags->args, long);
		charteger_l = ft_itoa_long_long(long_num);
		flags->wordlen = ft_strlen(charteger_l);
		if ((flags->wordlen - flags->precision) > 0)
			flags->padding = (flags->length - flags->wordlen);
		else
			flags->padding = 0;
		padding(flags, 0);
		while (charteger_l[index] && (flags->num_type & (1 << F_LONG)))
			flags->total_length += write(1, &charteger_l[index++], 1);
		padding(flags, 1);
	}
	else
	{
		longlong_num = va_arg(flags->args, long long);
		charteger_ll = ft_itoa_long_long(longlong_num);
		flags->wordlen = ft_strlen(charteger_ll);
		if ((flags->wordlen - flags->precision) > 0)
			flags->padding = (flags->length - flags->wordlen);
		else
			flags->padding = 0;
		padding(flags, 0);
		while (charteger_ll[index] && (flags->num_type & (1 << F_LONG)))
			flags->total_length += write(1, &charteger_ll[index++], 1);
		padding(flags, 1);
	}
	if (charteger_l)
		free(charteger_l);
	if (charteger_ll)
		free(charteger_ll);
	charteger_l = NULL;
	charteger_ll = NULL;
}

void	ft_print_integer(t_printf *flags)
{
	int			integer;
	char		*charteger;
	int			index;

	index = 0;
	charteger = NULL;
	integer = va_arg(flags->args, int);
	charteger = ft_itoa(integer);
	flags->wordlen = ft_strlen(charteger);
	if ((flags->wordlen - flags->precision) > 0)
		flags->padding = (flags->length - flags->wordlen);
	else
		flags->padding = 0;
	padding(flags, 0);
	while (charteger[index])
		flags->total_length += write(1, &charteger[index++], 1);
	padding(flags, 1);
	free(charteger);
	charteger = NULL;
}

static int	convert_hex(int num)
{
	if (num <= 9)
		return (num + '0');
	return (num - 10 + 'a');
}

char		*itoa_hexadecimal(long long int value)
{
	long long int	num;
	char			*str;
	int				n;

	num = value;
	n = 0;
	while (num >= 16)
	{
		num = num / 16;
		n++;
	}
	str = (char *)malloc((n + 1) * sizeof(str));
	if (str)
	{
		str[n + 1] = '\0';
		while (n >= 0)
		{
			num = value % 16;
			str[n] = convert_hex(num);
			value = value / 16;
			n--;
		}
	}
	return (str);
}

// 	unsigned int as a hexadecimal number. x uses lower-case letters and X uses upper-case. 
void	ft_print_hexa(t_printf *flags, char format)
{
	int		integer;
	int		index;
	char	*charteger;
	char	caps;

	//printf("asdflags: %c\n", format);
	index = 0;
	//printf("flag: %d\n", flags->flag);
	if (format == 'X')
		flags->caps_on = 1;
	integer = va_arg(flags->args, int);
	charteger = itoa_hexadecimal(integer);
	flags->wordlen = ft_strlen(charteger);
	if ((flags->wordlen - flags->precision) > 0)
		flags->padding = (flags->length - flags->wordlen);
	else
		flags->padding = 0;
	padding(flags, 0);
	while (charteger[index])
	{
		//printf("flag: %d\n", flags->flag);
		if (index == 0 && flags->caps_on == 1 && flags->flag & (1 << F_PREFIX))
			flags->total_length += write(1, "0X", 2);
		else if (index == 0 && flags->caps_on == 0 && flags->flag & (1 << F_PREFIX))
			flags->total_length += write(1, "0x", 2);
		if (flags->caps_on == 1 && ft_isalpha(charteger[index]) == 1)
		{
			caps = charteger[index] - 32;
			flags->total_length += write(1, &caps, 1);
		}
		else
			flags->total_length += write(1, &charteger[index], 1);
		index++;
	}
	padding(flags, 1);
	free(charteger);
	charteger = NULL;
}
