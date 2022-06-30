/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 11:36:01 by jpuronah          #+#    #+#             */
/*   Updated: 2022/06/30 12:08:27 by jpuronah         ###   ########.fr       */
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

typedef struct s_flags
{

}				t_flags;

typedef struct s_printf
{
	va_list		args;
	char		*format;
	short		flag;
	int			total_length;
	int			number;
	int			wordlen;
}				t_printf;

int		ft_printf(const char *restrict format, ...);
void	print_error(char *reason, t_printf *flags);


void	ft_print_char(t_printf *flags);
void	ft_print_string(t_printf *flags);
void	ft_print_integer(t_printf *flags);
void	check_and_print_flags(t_printf *flags);



/*t_printf	*init_printf_flags(t_printf *flags);
void		ft_update_flags(t_printf *flags, const char *restrict format, int index);
void		set_flags(const char *format, int index, t_printf *flags);

void		ft_print_float_or_double(t_printf *flags);
void		ft_print_integer(t_printf *flags);
void		ft_print_char(t_printf *flags);
void		ft_print_percent(t_printf *flags, char percent);
void		ft_print_string(t_printf *flags);


*/

#endif
