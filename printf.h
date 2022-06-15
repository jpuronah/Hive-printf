#ifndef PRINTF_H
# define PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>

typedef struct s_printf
{
	va_list		args;
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

int		ft_printf(const char *restrict format, ...);

#endif
