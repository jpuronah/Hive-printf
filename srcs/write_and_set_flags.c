/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_and_set_flags.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 12:29:39 by jpuronah          #+#    #+#             */
/*   Updated: 2022/07/21 12:53:45 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

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

void	padding(t_printf *flags, int phase)
{
	char	ch;

	ch = 32;
	if (flags->flag & (1 << F_ZERO))
		ch = 48;
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
}

void	ft_no_conversion_specifier(t_printf *flags, char *format)
{
	flags->padding = flags->width - 1;
	if (flags->padding > 0)
	{
		padding(flags, 0);
		printf_write(flags, (char *)format, 1);
		padding(flags, 1);
		return ;
	}
	printf_write(flags, (char *)format, 1);
}
