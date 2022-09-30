/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 11:36:01 by jpuronah          #+#    #+#             */
/*   Updated: 2022/09/30 10:20:57 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# include "../libft/libft.h"
# include <stdarg.h>
# include <stdio.h>
//pois
# define F_PREFIX 0
# define F_SPACE 1
# define F_PLUS 2
# define F_MINUS 3
# define F_ZERO 4
//# define F_WILDCARD 5
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
	int			min_length;
	int			num_length;
	short		numchar;

	int			width;
	int			precision;
	int			padding;
	int			zero_pad_precision;

	int			length_written;
	int			wordlen;
	int			charlen;
}				t_printf;

/* ------------------------------ Prototypes -------------------------------- */

int		ft_printf(const char *format, ...);

void	reset_flags(t_printf *flags);
void	free_flags(t_printf *flags);

/* -------------------------- Parsing Functions ----------------------------- */

int		parse_flags(char *format, int index, t_printf *flags);
int		parse_width(char *format, int index, t_printf *flags);
int		parse_precision(char *format, int index, t_printf *flags);
int		parse_l(char *format, int index, t_printf *flags);
int		parse_h(char *format, int index, t_printf *flags);

//int		check_unsigned_and_l(char *format, int index, t_printf *flags);

/* ------------------------ Print & Padding --------------------------------- */

void	printf_write(t_printf *flags, void *new, size_t size);
void	padding(t_printf *flags, int phase);

/* -------------------- Strings & Chars Functions --------------------------- */

void	ft_print_char(t_printf *flags, char ch);
void	ft_print_string(t_printf *flags);
//void	ft_no_conversion_specifier(t_printf *flags, char *format);

/* -------------------- va_arg Numbers Functions ---------------------------- */

void	get_va_arg(t_printf *flags);
void	get_va_arg_base(char format, t_printf *flags);
void	get_va_arg_float_double(t_printf *flags);

/* ------------------------ I to A Functions -------------------------------- */

void	itoa_printf(intmax_t number, t_printf *flags, int length);
void	itoa_base_printf(uintmax_t number, t_printf *flags, int base);
void	itoa_base_fill(uintmax_t tmp, int base,
			char *number_as_char, t_printf *flags);

void	print_pointer_address(t_printf *flags);

void	get_number_length(t_printf *flags, intmax_t number);

/* ------------------------ Bonus Functions --------------------------------- */

#endif
