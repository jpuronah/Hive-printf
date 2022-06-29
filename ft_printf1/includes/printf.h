#ifndef PRINTF_H
# define PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stdio.h>
# include <math.h>

typedef struct s_printf
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
}				t_printf;

int			ft_printf(const char *restrict format, ...);
char		*ft_itoa_double(double dubbel, t_printf *flags);



t_printf	*init_printf_flags(t_printf *flags);
void		ft_update_flags(t_printf *flags, const char *restrict format, int index);
void		set_flags(const char *format, int index, t_printf *flags);


void		ft_print_float_or_double(t_printf *flags);
void		ft_print_integer(t_printf *flags);
void		ft_print_char(t_printf *flags);
void		ft_print_percent(t_printf *flags, char percent);
void		ft_print_string(t_printf *flags);

#endif
