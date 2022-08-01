/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_padding_flags.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 12:29:39 by jpuronah          #+#    #+#             */
/*   Updated: 2022/07/27 14:43:32 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"
/*
	Täält ft_strdup pois, koska void* new ei aina lopu '\0'
		-> segfault strdupis
*/

void	printf_write(t_printf *flags, void *new, size_t size)
{
	int		index;
	size_t	hold_size;
	char	*string;
	char	tmp;

	index = 0;
	tmp = 0;
	hold_size = size;
	string = ft_strdup((char *)new);
	while (size--)
	{
		if (ft_islower(string[index]) == 1 && flags->flag & (1 << F_CAPS_ON))
		{
			tmp = string[index++] - 32;
			write(1, &tmp, 1);
		}
		else
			write(1, &string[index++], 1);
	}
	flags->length_written += hold_size;
	flags->precision = 1;
	free(string);
}

static char	set_ch(t_printf *flags)
{
	char	ch;

	ch = 32;
	if (flags->flag & (1 << F_ZERO))
		ch = 48;
	if (flags->zero_pad_precision > 0)
		ch = 32;
	return (ch);
}

void	padding(t_printf *flags, int phase)
{
	char	ch;

	ch = set_ch(flags);
	if (flags->padding > -1)
	{
		if (!phase && !(flags->flag & (1 << F_MINUS)))
		{
			while (flags->padding > 0)
			{
				flags->length_written += write(1, &ch, 1);
				flags->padding--;
			}
		}
		else if (phase && (flags->flag & (1 << F_MINUS)))
		{
			while (flags->padding > 0)
			{
				write(1, &ch, 1);
				flags->length_written++;
				flags->padding--;
			}
		}
	}
}

void	free_flags(t_printf *flags)
{
	if (flags)
	{
		if (flags->format_string)
		{
			free(flags->format_string);
			flags->format_string = NULL;
		}
		free(flags);
		flags = NULL;
	}
}

void	reset_flags(t_printf *flags)
{
	flags->flag = 0;
	flags->num_type = 0;
	flags->num_length = 0;
	flags->numchar = 0;
	flags->width = 0;
	flags->precision = 1;
	flags->padding = 0;
	flags->wordlen = 0;
	flags->charlen = 0;
	flags->zero_pad_precision = 0;
	flags->min_length = 0;
}