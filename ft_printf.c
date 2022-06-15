/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:16:07 by jpuronah          #+#    #+#             */
/*   Updated: 2022/06/15 17:40:43 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include <stdio.h>

t_printf	*init_printf_flags(t_printf *flags)
{
	flags->width = 0;
	flags->precision = 0;
	flags->zero_padding = 0;
	flags->point = 0;
	flags->dash = 0;
	flags->total_length = 0;
	flags->sign = 0;
	flags->is_zero = 0;
	flags->percentage = 0;
	flags->space_flag = 0;
	return (flags);
}

/*
c = va_arg(args, int)
s = va_arg(args, char *)
d = va_arg(args, int)
i = va_arg(args, int)
u = va_arg(args, unsigned int)
p = va_arg(args, unsigned long)# or #(unsigned long)va_arg(args, void *);
x = va_arg(args, unsigned int)
X = va_arg(args, unsigned int)
*/

/*void	ft_update_flags(t_printf flags, int i)
{

}*/

int	ft_print_char(t_printf *flags)
{
	int	c;
	int		index;

	c = va_arg(flags->args, int);
	index = 1;
	//ft_update_flags(flags, 1);
	//if (flags->width && !flags->dash)
	//	ft_right_side_cs(flags, 0);
	flags->total_length += write(1, &c, 1);
	//if (flags->width && flags->dash)
	//	ft_left_side_cs(flags, 0);*/
	va_end(flags->args);
	return (index);
}

int	ft_print_string(t_printf *flags)
{
	char	*s;
	int		index;

	s = va_arg(flags->args, char *);
	index = 0;
	//ft_update_flags(flags, 1);
	//if (flags->width && !flags->dash)
	//	ft_right_side_cs(flags, 0);
	//while (*s)
	//	flags->total_length += write(1, &(*s++), 1);
	while (s[index])
		flags->total_length += write(1, &s[index++], 1);
	//if (flags->width && flags->dash)
	//	ft_left_side_cs(flags, 0);*/
	va_end(flags->args);
	return (index);
}


int		evaluate_format_type(const char *restrict format, t_printf *flags, int index)
{
	int		return_value;

	return_value = 0;
	while (format[index] != 's' && format[index] != 'c' && format[index] != 'd')
	{
		if (format[index] == '.')
			flags->point = 1;
		if (format[index] == '-')
			flags->dash = 1;
		if (format[index] == '0')
			flags->is_zero = 1;
		if (format[index] == '%')
			flags->percentage = 1;
		if (format[index] == '.')
			flags->point = 1;
		if (format[index] == '.')
			flags->precision = 1;
		if (format[index] == '-')
			flags->sign = -1;
		//space_flag, total_length, width, padding uupuu
		index++;
	}
	if (format[index] == 'c')
		return_value = ft_print_char(flags);
	if (format[index] == 's')
		return_value = ft_print_string(flags);
	/*if (format[index] == 'd' || format == 'i')
		ft_putnbr(flags);*/
	return (index);
}



int		ft_printf(const char *restrict format, ...)
{
	t_printf	*flags;
	int			index;
	int			return_value;

	flags = NULL;
	flags = (t_printf *)malloc(sizeof(t_printf));
	if (flags == NULL)
		return (-1);
	flags = init_printf_flags(flags);
	//printf_loop(format, flags);
	index = 0;
	return_value = 0;
	va_start(flags->args, format);
	while (format[index] != '\0')
	{
		printf("index: %d\n", index);
		if (format[index] == '%')
		{
			index += evaluate_format_type(format, flags, index + 1);
		}
		else
		{
			//printf("else");
			return_value += write(1, &format[index], 1);
		}
		index++;
	}
	va_end(flags->args);
	return_value += flags->total_length;
	free(flags);
	return (return_value);
}

int	main(int ac, char **av)
{
	char	*str;
	int		return_value;

	//str = "5";
	if (ac == 2)
	{
		str = ft_strdup(av[1]);
		return_value = ft_printf("%s", (const char *restrict)str);
		printf("\nret: %d\n", return_value);
		return_value = printf("%s", (const char *restrict)str);
		printf("\nret: %d\n", return_value);
	}
	else
	{
		str = "sana";
		return_value = ft_printf("%s", (const char *restrict)str);
		printf("\nret: %d\n", return_value);
		return_value = printf("%s", (const char *restrict)str);
		printf("\nret: %d\n", return_value);
	}
}
