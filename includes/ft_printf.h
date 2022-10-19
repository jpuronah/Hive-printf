/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 11:36:01 by jpuronah          #+#    #+#             */
/*   Updated: 2022/10/18 11:06:51 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <stdarg.h>

# define PREFIX 0
# define SPACE 1
# define PLUS 2
# define MINUS 3
# define ZERO 4
# define LONG 6
# define LONGLONG 7
# define SHORT 8
# define SHORTCHAR 9
# define CAPS_ON 10
# define PRECISION 11
# define MAXINT 12
# define UNSIGNED 13
# define POINTER 14
# define SIZET 15

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
	int			field_width;
	int			precision;
	int			padding;
	int			zero_pad_precision;

	int			length_written;
	int			wordlen;
	int			charlen;

	int			negative_float;
	int			padding_char;
	int			float_sign_written;
}				t_printf;

/* ------------------------------ Prototypes -------------------------------- */

int			ft_printf(const char *format, ...);

void		reset_vars(t_printf *vars);
void		free_vars(t_printf *vars);

/* -------------------------- Parsing Functions ----------------------------- */

int			parse_flags(char *format, int index, t_printf *vars);
int			parse_width(char *format, int index, t_printf *vars);
int			parse_precision(char *format, int index, t_printf *vars);
int			parse_l(char *format, int index, t_printf *vars);
int			parse_h(char *format, int index, t_printf *vars);

/* ------------------------ Print & Padding --------------------------------- */

void		printf_write(t_printf *vars, void *new, size_t size);
void		padding(t_printf *vars, int phase);
void		padding_float(t_printf *vars);
void		adjust_padding_float(t_printf *vars);

/* -------------------- Strings & Chars Functions --------------------------- */

void		ft_print_char(t_printf *vars, char ch);
void		ft_print_string(t_printf *vars);

/* -------------------- va_arg Numbers Functions ---------------------------- */

void		get_va_arg(t_printf *vars);
void		get_va_arg_base(char format, t_printf *vars);
void		get_va_arg_float_double(t_printf *vars);

/* ------------------------ I to A Functions -------------------------------- */

void		itoa_printf(intmax_t number, t_printf *vars, int length);
void		itoa_base_printf(uintmax_t number, t_printf *vars, int base);
void		itoa_base_fill(uintmax_t tmp, int base,
				char *number_as_char, t_printf *vars);
void		print_pointer_address(t_printf *vars);

/* ------------------------- Helper Functions ------------------------------- */

void		get_number_length(t_printf *vars, intmax_t number);
char		*malloc_number_as_char(int size);
void		free_number_as_char(char *number_as_char);
long double	round_float(t_printf *vars, long double float_number);

#endif
