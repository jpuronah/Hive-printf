/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 14:36:13 by jpuronah          #+#    #+#             */
/*   Updated: 2022/07/20 16:05:20 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

static void	free_flags(t_printf *flags)
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

static t_printf	*init_and_malloc_structure(void)
{
	t_printf	*flags;

	flags = NULL;
	flags = (t_printf *)malloc(sizeof(t_printf));
	if (flags == NULL)
		return (NULL);
	flags->format_string = NULL;
	flags->flag = 0;
	flags->num_type = 0;
	flags->num_length = 0;
	flags->numchar = 0;
	flags->length_written = 0;
	//flags->padding_length = 0;
	flags->width = 0;
	flags->precision = 1;
	flags->padding = 0;
	flags->wordlen = 0;
	flags->charlen = 0;
	return (flags);
}

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
	//printf("%s\n", string);
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

void	default_flags(t_printf *flags)
{
	flags->flag = 0;
	flags->num_type = 0;
	flags->num_length = 0;
	flags->numchar = 0;
	//flags->padding_length = 0;
	flags->width = 0;
	flags->precision = 1;
	flags->padding = 0;
	flags->wordlen = 0;
	flags->charlen = 0;
}

int	evaluate_format_type(char *format, int index, t_printf *flags)
{
	if (format[index] == '%')
		index++;
	index = parse_flags(format, index, flags);
	index = parse_width(format, index, flags);
	index = parse_precision(format, index, flags);
	index = parse_h_l(format, index, flags);
	/*printf("%d\n", flags->width);
	printf("%d\n", flags->precision);
	printf("%d\n", flags->num_length);
	printf("%d\n", flags->num_type);
	printf("%d\n", flags->padding);*/
	index = conversion_specifiers(format, index, flags);
	default_flags(flags);
	return (index);
}

int	ft_printf(const char *format, ...)
{
	t_printf	*flags;
	int			return_value;
	int			index;

	flags = NULL;
	flags = init_and_malloc_structure();
	index = 0;
	flags->format_string = ft_strdup((char *)format);
	va_start(flags->args, format);
	while (flags->format_string[index] != '\0')
	{
		if (flags->format_string[index] == '%')
		{
			if (!flags->format_string[index + 1])
				break ;
			index = evaluate_format_type(flags->format_string, index, flags);
		}
		else
			flags->length_written += write(1, &flags->format_string[index], 1);
		index++;
	}
	va_end(flags->args);
	return_value = flags->length_written;
	free_flags(flags);
	return (return_value);
}
