#include <stdio.h>
#include "includes/printf.h"

int	main(int ac, char **av)
{
	char		*str;
	int			integer;
	double		dubbel;
	int			return_value;
	char		param;
	t_printf	*flags;

	integer = 0;
	dubbel = 1230.000865;
	integer = 55;
	str = "sana";

	printf("own printf:\n");
	ft_printf("%x", -42);
	printf("|\n**********************\n");
	/*ft_printf("%c", 'a');
	printf("|\n**********************\n");
	ft_printf("%%");
	printf("|\n**********************\n");*/

	printf("\nreal printf:\n");
	printf("%x", -42);
	printf("|\n**********************\n");
	/*return_value = ft_printf("%p, %%, %s, %d, %c, %i, %.1f", str, (const char *restrict)str, integer, str[2], integer / 2, dubbel);
	printf("\noma ret: %d\n", return_value);
	return_value = printf("%p, %%, %s, %d, %c, %i, %.1f", str, (const char *restrict)str, integer, str[2], integer / 2, dubbel);
	printf("\noikee ret: %d\n", return_value);*/
	return (0);
}
