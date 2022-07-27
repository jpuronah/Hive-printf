#include <stdio.h>
#include "includes/printf.h"

int	main(int ac, char **av)
{
	printf("own printf:\n");
	ret = ft_printf("%f", -1.234);
	printf("|\nret: %d\n", ret);
	printf("\n**********************\n");

	printf("\nreal printf:\n");
	ret = printf("%f", -1.234);
	printf("|\nret: %d\n", ret);
	printf("\n**********************\n");
	return (0);
}
