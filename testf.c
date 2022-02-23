#include "printf.h"

int	main(int ac, char **av)
{
	char	*str = "kakka";

	printf("Paska sekä %-2s\n", str);
	printf("%.*d\n", 8, 12);
	printf( "%-90s %s\n", "Starting initialization...", "Ok." );
	return (0);
}
