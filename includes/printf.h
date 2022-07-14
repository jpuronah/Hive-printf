/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 11:36:01 by jpuronah          #+#    #+#             */
/*   Updated: 2022/07/14 13:38:50 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stdio.h>
# include <math.h>

# include <errno.h>// ??!?!

# define F_PREFIX 0
# define F_SPACE 1
# define F_PLUS 2
# define F_MINUS 3
# define F_ZERO 4
# define F_ASTERISK 5
# define F_LONG 6
# define F_LONGLONG 7
# define F_SHORT 8
# define F_SHORTCHAR 9
# define F_CAPS_ON 10
# define F_PRECISION 11
# define F_MAXINT 12
# define F_UNSIGNED 13
# define F_POINTER 14
# define F_SIZET 15

typedef struct s_printf
{
	va_list		args;

	char		*format_string;

	short		flag;
	short		num_type;
	int			num_length;
	short		numchar;

	int			padding_length;
	int			width;
	int			precision;
	int			padding;
	int			caps_on;

	int			length_written;
	int			wordlen;
	int			charlen;

	char		*format;
}				t_printf;

int		ft_printf(const char *format, ...);

int		evaluate_format_type(const char *format, int index, t_printf *flags);
int		conversion_specifiers(const char *format, int index, t_printf *flags);
int		parse_flags(const char *format, int index, t_printf *flags);
int		parse_precision(const char *format, int index, t_printf *flags);
int		parse_width(const char *format, int index, t_printf *flags);
int		parse_h_l(const char *format, int index, t_printf *flags);

void	printf_write(t_printf *flags, void *new, size_t size);
void	padding(t_printf *flags, int phase);

void	ft_print_char(t_printf *flags, char ch);
void	ft_print_string(t_printf *flags);

void	get_va_arg(t_printf *flags);
void	get_va_arg_base(int base, t_printf *flags);
void	get_va_arg_float_double(t_printf *flags);

void	ft_print_integer(t_printf *flags);
void	ft_print_unsigned(t_printf *flags);
void	ft_print_long_long(t_printf *flags);
void	ft_print_float_double(t_printf *flags);

void	print_pointer_address(t_printf *flags);

void	pf_putdouble(t_printf *p);

//void	itoa_printf(intmax_t number, t_printf *flags, int length);
//void	itoa_base_fill(uintmax_t tmp, int base, char s[21], t_printf *flags);

int			ft_strchri(const char *s, int c, int index);
int			ft_strchri_lu(const char *s, int c, int index);
int			ft_islower(int c);
int			ft_is_capital(int c);
int			ft_min(int a, int b);
int			ft_max(int a, int b);
char		*ft_itoa_long_long(long long n);
double		ft_pow(double n, int pow);
long long	ft_abs_ll(long long i);

#endif
