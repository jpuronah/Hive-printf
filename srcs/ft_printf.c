/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 16:36:01 by jpuronah          #+#    #+#             */
/*   Updated: 2022/06/27 19:43:56 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
//#include <ft_printf.h>

void	free_flags(t_printf *flags)
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

/*
static int		conv_ex(int nb)
{
	if (nb >= 10)
		return (nb - 10 + 'a');
	else
		return (nb + '0');
}

char	*itoa_base(int value, int base)
{
	int					i;
	char				*str;
	int					tmp;
	
	i = 0;
	tmp = value;
	while (tmp >= base)
	{
		tmp = tmp / base;
		i++;
	}	
	if (!(str = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	str[i + 1] = '\0';
	while (i >= 0)
	{
		tmp = value % base;
		str[i] = conv_ex(tmp);
		value /= base;
		i--;
	}
	return (str);
}*/

static int	conv_hex(int nb)
{
	if (nb <= 9)
		return (nb + '0');
	return (nb - 10 + 'a');
}

char		*itoa_hex(long long int value)
{
	char	*str;
	int	n;
	long long int	nb;

	nb = value;
	n = 0;
	while (nb >= 16)
	{
		nb = nb / 16;
		n++;
	}
	str = (char *)malloc((n + 1) * sizeof(str));
	if (str)
	{
		str[n + 1] = '\0';
		while (n >= 0)
		{
			nb = value % 16;
			str[n] = conv_hex(nb);
			value = value / 16;
			n--;
		}
	}
	return (str);
}

void	ft_print_pointer(t_printf *flags)
{
	int				index;
	unsigned long	p;
	char			*charteger;

	printf("Make shift solution SOS\n");
	//exit(0);
	p = va_arg(flags->args, unsigned long);
	//p = (unsigned long)va_arg(flags->args, void *);
	//charteger = itoa_base(p, 16);
	charteger = itoa_hex(p);
	//printf("lu: %lu", p);
	ft_putstr("0x");
	index = 0;
	while (charteger[index])
		flags->total_length += write(1, &charteger[index++], 1);

}

static void	conversion_specifier(char format, t_printf *flags)
{
	if (format == '%')
		ft_print_percent(flags, '%');
	if (format == 'c')
		ft_print_char(flags);
	if (format == 's')
		ft_print_string(flags);
	if (format == 'd' || format == 'i' || format == 'D')
		ft_print_integer(flags);
	if (format == 'f')
		ft_print_float_or_double(flags);
	if (format == 'p')
		ft_print_pointer(flags);
	if (format == 'o')
		printf("error: an octal (base 8) integer needed\n");
	if (format == 'u')
		printf("error: unsigned int decimal\n");
	if (format == 'x' || format == 'X')
		printf("error: a hexadecimal (base 16) integer\n");
	if (format == 'e' || format == 'E')
		printf("error: a floating point number in scientific notation\n");
	if (format == 'l' || format == 'L')
		printf("error: long / long long something\n");
	if (format == 'n')
		printf("error: prints nothing\n");
	if (format == 'h')
		printf("error: %%hi short integer, %%hu short unsigned integer)\n");
	/*if (format[index] == 'p')
	if (format[index] == 'o')
	if (format[index] == 'u')
	if (format[index] == 'x' || format[index] == 'X')
	*/
}

//Tänne tulee format[index + 1], eli '%' jälkeinen merkki	//
static void		evaluate_format_type(const char *restrict format, t_printf *flags, int index)
{
	//"You must manage the minimum field-width, You must manage the precision"
	if (ft_strchr("# +-0*.", format[index]))
	{
		printf("\n\n*** ** *   flags skipped (\"# +-0*.\")  * ** *** \n\n");
		set_flags(format, index, flags);
		ft_update_flags(flags, format, index);
	}
	else if (ft_strchr("cspdiouxXfnh%", format[index]))
		conversion_specifier(format[index], flags);
	else
		print_error("error: Format error", flags);
}

int		ft_printf(const char *restrict format, ...)
{
	t_printf	*flags;
	int			index;
	int			return_value;

	flags = NULL;
	flags = init_printf_flags(flags);
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
