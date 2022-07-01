/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:30:54 by jpuronah          #+#    #+#             */
/*   Updated: 2022/07/01 14:14:55 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	padding(t_printf *flags, int phase)
{
	char	ch;

	ch = 32;
	if (flags->flag & (1 << F_ZERO))
		ch = 48;
	if (flags->padding > 0)
	{
		if (!phase && !(flags->flag & (1 << F_MINUS)))
		{
			while (flags->padding > 0)
			{
				write(1, &ch, 1);
				flags->total_length++;
				flags->padding--;
			}
		}
		else if (phase && (flags->flag & (1 << F_MINUS)))
		{
			while (flags->padding > 0)
			{
				write(1, &ch, 1);
				flags->total_length++;
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
	//if (c & (1 << F_LONG))
	//	flags->charlen = ft_charlen(c);
	flags->charlen = 1;
	flags->padding = flags->length - flags->charlen;
	if (flags->padding < 0)
		flags->padding = 0;
	padding(flags, 0);
	if (flags->charlen == 1)
		flags->total_length += write(1, &c, 1);
	padding(flags, 1);
}

void	print_null_string(char *string, t_printf *flags)
{
	if (!string)
	{
		if (!(flags->flag & (1 << F_ZERO)))
			write(1, "(null)", 6);
		else
			while (flags->length--)
				write(1, "0", 1);
	}
	else
		write(1, string, (int)ft_strlen(string));
}

void	ft_print_string(t_printf *flags)
{
	char	*string;
	int		index;

	index = 0;
	string = va_arg(flags->args, char *);
	printf("string: %s\n", string);
	if (!string)
	{
		printf("paskasa\n");
		print_null_string(string, flags);
	}
	else
	{
		flags->wordlen = ft_strlen(string);
		if ((flags->length - flags->precision) > 0)
			flags->padding = (flags->length - (flags->wordlen - flags->precision));
		else
			flags->padding = 0;
		printf("%d\n", flags->length);
		printf("%d\n", flags->wordlen);
		printf("%d\n", flags->precision);
		padding(flags, 0);
		if (flags->precision > 0)
			while (string[index] && flags->precision--)
				flags->total_length += write(1, &string[index++], 1);
		
		else
			while (string[index])
				flags->total_length += write(1, &string[index++], 1);
		padding(flags, 1);
	}
}

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
	if (format == 'X')
		flags->flag = (1 << F_CAPS_ON);
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
}