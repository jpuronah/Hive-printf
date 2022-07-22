/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_double_pointer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 10:48:02 by jpuronah          #+#    #+#             */
/*   Updated: 2022/07/22 13:02:38 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

static char	check_flags(t_printf *flags, char *string, long double number)
{
	char	tmp;

	tmp = string[0];
	if (flags->flag & (1 << F_PRECISION) && flags->flag & (1 << F_ZERO))
		tmp = ' ';
	if (flags->flag & (1 << F_SPACE))
		tmp = ' ';
	if (number < 0)
		tmp = '-';
	if (flags->flag & (1 << F_PLUS) && number >= 0)
		tmp = '+';
	return (tmp);
}

void	long_double_float_toa_fill(long double number, t_printf *flags, long num)
{
	int		length;
	int		accuracy;
	char	*string;

	//printf("number: %Lf\n", number);
	//printf("num: %ld\n", num);
	string = NULL;
	length = flags->num_length - 1 - flags->precision;
	accuracy = flags->num_length - 1 - length;
	string = ft_memalloc((size_t)(accuracy + length + 1));
	//printf("accu: %d\n", accuracy);
	//printf("length: %d\n", length);
	while (accuracy--)
	{
		//printf("%d: ", length + accuracy + 1);
		//printf("num1: %ld\n", num % 10);
		string[length + accuracy + 1] = (num % 10 + '0');
		num /= 10;
	}
	if (flags->precision > 0)
		string[length] = '.';
	num = ft_abs_ll((long long)number);
	while (accuracy < length)
	{
		//printf("%d: ", length - accuracy - 1);
		//printf("num2: %ld\n", num % 10);
		accuracy++;
		string[length - accuracy - 1] = num % 10 + '0';
		//printf("%c\n", string[length - accuracy - 1]);
		num /= 10;
	}
	string[0] = check_flags(flags, string, number);
	printf_write(flags, string, (size_t)flags->num_length);
	free(string);
	string = NULL;
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
