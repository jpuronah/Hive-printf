/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers_numbers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:45:34 by jpuronah          #+#    #+#             */
/*   Updated: 2022/07/04 21:51:43 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

/* CHARTEGER stuff gotta be gone */

void	ft_print_integer(t_printf *flags)
{
	int		integer;
	char	*charteger;
	int		index;

	index = 0;
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


static int	conv_hex(int num)
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
			str[n] = conv_hex(num);
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

	index = 0;
	//if (format == 'X')
	//	flags->flag = (1 << F_CAPS_ON);
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
		if (flags->flag & (1 << F_CAPS_ON) && ft_isalpha(charteger[index]) == 1)
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
