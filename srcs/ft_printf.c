#include "libft/libft.h"
#include "includes/printf.h"

int	ft_printf(const char *restrict format,)
{
	t_print *tab;

	printf("paska %d. %s \n", index, string);

	tab = (t_print *)malloc(sizeof(t_print));
	if (!tab)
		return (-1);
	ft_initialise_tab(tab);

	va_start(tab->args, format);
	i = -1;
	ret = 0;
	while (format[++i]) //while string exists
	{
		if (format[i] == '%') // if variaabeli
			i = ft_eval_format(tab, format, (i + 1)); //evaluoi formaatti
		else
			ret += write(1, &format[i], 1); // print shit
	}
	va_end(tab->args);
	ret += tab->tl;
	free (tab);
	return (ret);
}

int	main()
{
	ft_printf();
	return (0);
}