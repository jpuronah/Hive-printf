/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:16:07 by jpuronah          #+#    #+#             */
/*   Updated: 2022/06/16 12:19:26 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

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

int	ft_print_float_or_double(t_printf *flags)
{
	//printf("print_float\n");
	char	*s;
	double	d_num;
	float	f_num;
	int		index;
	char	*char_num;

	index = 0;
	d_num = va_arg(flags->args, double);
	char_num = ft_itoa_double(d_num, flags);
	while (char_num[index])
		flags->total_length += write(1, &char_num[index++], 1);
	//printf("%f\n", d_num);
	/*charteger = ft_itoa(integer);
	while (charteger[index])
		flags->total_length += write(1, &charteger[index++], 1);
	va_end(flags->args);*/
	return (index);
}

int	ft_print_integer(t_printf *flags)
{
	//printf("print_integer\n");
	char	*s;
	int		integer;
	int		index;
	char	*charteger;

	index = 0;
	integer = va_arg(flags->args, int);
	charteger = ft_itoa(integer);
	while (charteger[index])
		flags->total_length += write(1, &charteger[index++], 1);
	va_end(flags->args);
	return (index);
}

int	ft_print_char(t_printf *flags)
{
	//printf("print_char\n");
	int		c;
	int		index;

	c = va_arg(flags->args, int);
	index = 1;
	flags->total_length += write(1, &c, 1);
	va_end(flags->args);
	return (index);
}

int	ft_print_string(t_printf *flags)
{
	//printf("print_string\n");
	char	*s;
	int		index;

	s = va_arg(flags->args, char *);
	index = 0;
	while (s[index])
		flags->total_length += write(1, &s[index++], 1);
	va_end(flags->args);
	return (index);
}

void	ft_update_flags(t_printf *flags, const char *restrict format, int index)
{
	int	len;

	len = 0;
	if (flags->precision > 0)
	{
		if (ft_isdigit(format[index]) == 1)
		{
			len++;
			flags->precision = format[index] - 48;
		}
	}
}

int		evaluate_format_type(const char *restrict format, t_printf *flags, int index)
{
	int		return_value;

	return_value = 0;
	while (format[index] != 's' && format[index] != 'c' && format[index] != 'd' && format[index] != 'i' && format[index] != 'f')
	{
		if (format[index] == '.')
			flags->precision = 1;
		if (format[index] == '-')
			flags->dash = 1;
		if (format[index] == '0')
			flags->is_zero = 1;
		if (format[index] == '%')
			flags->percentage = 1;
		//space_flag, total_length, width, sign,, precision padding uupuu
		index++;
	}
	ft_update_flags(flags, format, index - 1);
	/*ft_update_flags(flags, 1);
	if (flags->width && !flags->dash)
		ft_right_side_cs(flags, 0);
	if (flags->width && flags->dash)
		ft_left_side_cs(flags, 0);*/
	if (format[index] == 'c')
		return_value = ft_print_char(flags);
	if (format[index] == 's')
		return_value = ft_print_string(flags);
	if (format[index] == 'd' || format[index] == 'i')
		return_value = ft_print_integer(flags);
	if (format[index] == 'f')
		return_value = ft_print_float_or_double(flags);
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
		if (format[index] == '%')
		{
			evaluate_format_type(format, flags, index + 1);
			index++;
		}
		else
			return_value += write(1, &format[index], 1);
		index++;
	}
	va_end(flags->args);
	return_value += flags->total_length;
	free(flags);
	return (return_value);
}

int	main(int ac, char **av)
{
	char		*str;
	int			integer;
	double		dubbel;;
	int			return_value;
	char		param;
	t_printf	*flags;

	integer = 0;
	flags = NULL;
	flags = (t_printf *)malloc(sizeof(t_printf));
	if (flags == NULL)
		return (-1);
	flags = init_printf_flags(flags);
	dubbel = 1230.000865;
	integer = 12345;
	str = "sana";

	/*ft_printf("%i\n", integer);
	printf("%i\n\n", integer);
	ft_printf("%d\n", integer);
	printf("%d\n\n", integer);
	ft_printf("%s\n", str);
	printf("%s\n\n", str);
	ft_printf("%f\n", dubbel);
	printf("%f\n", dubbel);*/
	return_value = ft_printf("%s, %d, %c, %i, %.4f", (const char *restrict)str, integer, str[2], integer / 2, dubbel);
	printf("\noma ret: %d\n", return_value);
	return_value = printf("%s, %d, %c, %i, %f", (const char *restrict)str, integer, str[2], integer / 2, dubbel);
	printf("\noikee ret: %d\n", return_value);
	/*
	if (ac == 2 && ft_isalpha(av[1][0]) == 1)
	{
		str = ft_strdup(av[1]);
		return_value = ft_printf("%s", (const char *restrict)str);
		printf("\nret: %d\n", return_value);
		return_value = printf("%s", (const char *restrict)str);
		printf("\nret: %d\n", return_value);
	}
	else if (ac == 2 && ft_isdigit(av[1][0]) == 1)
	{
		str = ft_strdup(av[1]);
		return_value = ft_printf("%s", (const char *restrict)str);
		printf("\nret: %d\n", return_value);
		return_value = printf("%s", (const char *restrict)str);
		printf("\nret: %d\n", return_value);
	}
	else if (ac == 1)
	{
		integer = 12345;
		return_value = ft_printf("%d", integer);
		printf("\nret: %d\n", return_value);
		return_value = printf("%d", integer);
		printf("\nret: %d\n", return_value);
	}
	else
	{
		str = "sana";
		return_value = ft_printf("%s", (const char *restrict)str);
		printf("\nret: %d\n", return_value);
		return_value = printf("%s", (const char *restrict)str);
		printf("\nret: %d\n", return_value);
	}*/
}
