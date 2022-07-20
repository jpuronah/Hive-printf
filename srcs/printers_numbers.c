/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers_numbers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:45:34 by jpuronah          #+#    #+#             */
/*   Updated: 2022/07/20 18:12:52 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

void	itoa_base_fill(uintmax_t tmp, int base, char s[21], t_printf *flags)
{
	int		len;

	if (tmp && !(flags->flag & (1 << F_POINTER)) && (flags->flag & (1 << F_ZERO))
		&& (flags->flag & (1 << F_PREFIX)) && base == 16
		&& !(flags->flag & (1 << F_LONGLONG))
		&& flags->num_length > 3)
		flags->num_length -= 2;
	len = flags->num_length;
	flags->numchar = 'a' - 10;
	if (flags->flag & (1 << F_CAPS_ON))
		flags->numchar = 'a' - 10 - 32;
	while (len--)
	{
		if (tmp % (uintmax_t)base < 10)
			s[len] = (char)(tmp % (uintmax_t)base + '0');
		else
			s[len] = (char)(tmp % (uintmax_t)base + (uintmax_t)flags->numchar);
		tmp /= (uintmax_t)base;
	}
	if (flags->flag & (1 << F_PRECISION) && flags->flag & (1 << F_ZERO))
		s[0] = ' ';
}

static void	pad_adjust_base(uintmax_t number, t_printf *flags, int oct_zero_check, int base)
{
	if (flags->flag & (1 << F_ZERO))
		flags->precision = flags->width;
	flags->num_length = ft_max(flags->precision, flags->num_length);
	if (flags->flag & (1 << F_PREFIX) && base == 8 && oct_zero_check == 0)
		flags->width--;
	if (flags->flag & (1 << F_PREFIX) && base == 8 && number == 0
		&& flags->flag & (1 << F_PRECISION))
		flags->num_length++;
	if (flags->num_length < flags->width)
		flags->padding = flags->width - flags->num_length;
	if (flags->flag & (1 << F_PREFIX) && base == 16
		&& !(flags->flag & (1 << F_ZERO)))
	{
		flags->padding = ft_max(0, (flags->width - flags->num_length));
		if (flags->flag & (1 << F_PREFIX))
			flags->padding -= 2;
	}
}

void	itoa_base_printf(uintmax_t number, t_printf *flags, int base)
{
	char		number_as_char[210];
	uintmax_t	tmp;
	int			oct_zero_check;

	oct_zero_check = 0;
	flags->num_length = 0;
	tmp = number;
	while (tmp)
	{
		tmp /= (uintmax_t)base;
		flags->num_length++;
	}
	if (flags->num_length < flags->precision)
		oct_zero_check = 1;
	pad_adjust_base(number, flags, oct_zero_check, base);
	padding(flags, 0);
	if ((number || flags->flag & (1 << F_POINTER))
		&& (flags->flag & (1 << F_PREFIX)
			&& ((base == 8 && oct_zero_check == 0) || base == 16)))
		printf_write(flags, "0", 1);
	if ((number || (flags->flag & (1 << F_POINTER)))
		&& (flags->flag & (1 << F_PREFIX) && base == 16))
	{
		if (flags->flag & (1 << F_CAPS_ON))
			printf_write(flags, "X", 1);
		else
			printf_write(flags, "x", 1);
	}
	itoa_base_fill(number, base, number_as_char, flags);
	printf_write(flags, number_as_char, (size_t)flags->num_length);
	padding(flags, 1);
}

void	get_va_arg_base(int base, t_printf *flags)
{
	uintmax_t	number;

	//printf("type: %d\n", flags->num_type);
	//printf("flag: %d\n", flags->flag);
	if (flags->num_type & (1 << F_LONG))
		number = ((uintmax_t)va_arg(flags->args, unsigned long));
	else if (flags->num_type & (1 << F_LONGLONG))
		number = ((uintmax_t)va_arg(flags->args, unsigned long long));
	else if (flags->num_type & (1 << F_SHORT))
	{
		//printf("short\n");
		number = (uintmax_t)((unsigned short)va_arg(flags->args, int));
	}
	else if (flags->num_type & (1 << F_SHORTCHAR))
	{
		//printf("short\n");
		number = (uintmax_t)((unsigned char)va_arg(flags->args, int));
	}
	else if (flags->num_type & (1 << F_SIZET))
		number = ((uintmax_t)va_arg(flags->args, size_t));
	else
	{
		number = ((uintmax_t)va_arg(flags->args, unsigned int));
	}
	if (flags->flag & (1 << F_ZERO))
		flags->precision = flags->width;
	//else if (flags->num_type & (1 << F_MAXINT))
	//	number = (va_arg(flags->args, uintmax_t));
	//printf("num: %jd\n", number);
	itoa_base_printf(number, flags, base);
}

static void	pad_adjust_did(intmax_t number, int length, t_printf *flags)
{
	
	//				flags->padding, flags->precision, flags->width);
	if ((number < 0 || flags->flag & (1 << F_PLUS)
			|| flags->flag & (1 << F_SPACE)) && flags->flag & (1 << F_ZERO))
		--flags->precision;
	flags->num_length = ft_max(length, flags->precision);
	if (number < 0 || flags->flag & (1 << F_PLUS)
		|| flags->flag & (1 << F_SPACE))
		flags->num_length++;
	if (flags->num_length < flags->width)
		flags->padding = flags->width - flags->num_length;
}

void	itoa_printf(intmax_t number, t_printf *flags, int length)
{
	char		number_as_char[210];
	uintmax_t	tmp;

	tmp = (uintmax_t)ft_abs_ll((long long)number);
	if (tmp == 0 && flags->flag & (1 << F_ZERO))
		length++;
	while (tmp)
	{
		tmp /= 10;
		++length;
	}
	pad_adjust_did(number, length, flags);
	padding(flags, 0);
	tmp = (uintmax_t)ft_abs_ll((long long)number);
	itoa_base_fill(tmp, 10, number_as_char, flags);
	if (flags->flag & (1 << F_SPACE))
		number_as_char[0] = ' ';
	if (number < 0)
		number_as_char[0] = '-';
	if (number >= 0 && flags->flag & (1 << F_PLUS))
		number_as_char[0] = '+';
	printf_write(flags, number_as_char, (size_t)flags->num_length);
	padding(flags, 1);
}

void	get_va_arg(t_printf *flags)
{
	intmax_t	number;

	//printf("type: %d\n", flags->num_type);
	if (flags->num_type & (1 << F_LONG))
	{
		//printf("1\n");
		number = (intmax_t)va_arg(flags->args, long);
	}
	else if (flags->num_type & (1 << F_LONGLONG))
	{
		//printf("2\n");
		number = (intmax_t)va_arg(flags->args, long long);
	}
	else if (flags->num_type & (1 << F_SHORT))
	{
		//printf("3\n");
		number = (intmax_t)((short)va_arg(flags->args, int));
	}
	else if (flags->num_type & (1 << F_SHORTCHAR))
	{
		//printf("4\n");
		number = (intmax_t)((char)va_arg(flags->args, int));
	}
	else if (flags->num_type & (1 << F_MAXINT))
	{
		//printf("5\n");
		number = (va_arg(flags->args, intmax_t));
	}
	else if (flags->num_type & F_UNSIGNED)
	{
		//printf("6\n");
		number = ((intmax_t)va_arg(flags->args, ssize_t));
	}
	else
	{
		//printf("7\n");
		number = ((intmax_t)va_arg(flags->args, int));
	}
	if (flags->flag & (1 << F_ZERO))
	{
		//printf("8\n");
		flags->precision = flags->width;
	}
	//printf("%jd\n", number);
	itoa_printf(number, flags, 0);
}

void	print_pointer_address(t_printf *flags)
{
	void	*pointer;

	pointer = va_arg(flags->args, void *);
	flags->flag &= ~(1 << F_PREFIX);
	if (flags->flag & (1 << F_ZERO))
		flags->width -= 2;
	if (flags->num_length > flags->width - 3)
		flags->padding = flags->width - 3 - flags->num_length;
	flags->flag |= (1 << F_PREFIX);
	flags->flag |= (1 << F_POINTER);
	itoa_base_printf((uintmax_t)pointer, flags, 16);
	flags->flag = 0;
}
