#include <stdio.h>
#include <stdarg.h>

int	main(int ac, char **av)
{
	va_list			ap;
	char			c;
	char			*s;
	long long		p;
	int				di;
	unsigned int	uxX;

	c = va_arg(ap, int);
	s = va_arg(ap, char*);
	p = va_arg(ap, long long);
	di = va_arg(ap, int);
	uxX = va_arg(ap, unsigned int);


	va_start(ap, last);
	va_arg(ap, type);
	va_end(ap);

	//%[flags][width][.precision]type

	

}
