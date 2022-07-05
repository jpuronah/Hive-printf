/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 11:36:01 by jpuronah          #+#    #+#             */
/*   Updated: 2022/07/05 17:29:19 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stdio.h>
# include <math.h>

/*typedef struct s_printf
{
	va_list		args;
	int			left_pad;
	int			right_pad;
	int			width;
	int			precision;
	int			zero_padding;
	int			point;
	int			dash;
	int			total_length;
	int			sign;
	int			is_zero;
	int			percentage;
	int			space_flag;
}				t_printf;*/

# define F_PREFIX 0
# define F_SPACE 1
# define F_PLUS 2
# define F_MINUS 3
# define F_ZERO 4
# define F_ASTERISK 5
# define F_LONG 6
# define F_LONGLONG 7
# define F_SHORT 8
# define F_SHORTSHORT 9
# define F_CAPS_ON 10

typedef struct s_flags
{

}				t_flags;

typedef struct s_printf
{
	va_list		args;

	short		flag;
	short		num_type;
	int			length;
	int			precision;
	int			padding;
	int			caps_on;

	int			number;
	int			total_length;
	int			wordlen;
	int			charlen;

	char		*format;
}				t_printf;

int		ft_printf(const char *restrict format, ...);
void	print_error(char *reason, t_printf *flags);

int		parse_flags(const char *restrict format, int index, t_printf *flags);
int		parse_width_and_precision(const char *restrict format, int index, t_printf *flags);
int		parse_h_l(const char *restrict format, int index, t_printf *flags);

void	ft_print_char(t_printf *flags, char ch);
void	ft_print_string(t_printf *flags);

void	ft_print_integer(t_printf *flags);
void	ft_print_unsigned(t_printf *flags);
void	ft_print_long_long(t_printf *flags);

void	ft_print_float_double(t_printf *flags);

void	ft_print_hexa(t_printf *flags, char format);
void	ft_print_octal(t_printf *flags);
//void	check_and_print_flags(t_printf *flags);

void	padding(t_printf *flags, int phase);

int		ft_strchri(const char *s, int c, int index);
char	*ft_itoa_long_long(long long n);

#endif
