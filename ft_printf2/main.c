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
	integer = 12345;
	str = "sana";

	printf("own printf:\n");
	ft_printf("%10saa\n", str);
	printf("real printf:\n");
	printf("%10saa\n", str);
	
	/*return_value = ft_printf("%p, %%, %s, %d, %c, %i, %.1f", str, (const char *restrict)str, integer, str[2], integer / 2, dubbel);
	printf("\noma ret: %d\n", return_value);
	return_value = printf("%p, %%, %s, %d, %c, %i, %.1f", str, (const char *restrict)str, integer, str[2], integer / 2, dubbel);
	printf("\noikee ret: %d\n", return_value);*/
	return (0);
}
