#include "libft/libft.h"
#include "printf.h"

/*
	ft_printf is a project that mimics the real printf function.
	Although wide in scope, it’s not a difficult project.

	THINGS TO KEEP IN MIND before starting off:

----Conversions to handle: csdiupxX%----
	
	Flags to handle: 0-.*
	Value to return: length of the printed string (int).

	> man 3 printf
	[..]
	If the 0 and - flags both appear, the 0 flag is ignored. If a precision is 
	given with a numeric conversion (d, i, o, u, x, and X), the 0 flag is 
	ignored.
	[..]
*/



/*static void	ft_error(void)
{
	ft_putendl("error");
	exit(EXIT_FAILURE);
}*/

static void	usage(const char *prog_name)
{
	ft_putstr_fd("usage: ", STDERR_FILENO);
	ft_putstr_fd(prog_name, STDERR_FILENO);
	ft_putstr_fd(" [input_file]\n", STDERR_FILENO);
}

void ft_print_integer(t_print *tab)
{
	while (1)
		tab = NULL;
}

void ft_print_char(t_print *tab)
{
	char a;

	a = va_arg(tab->args, int);  // variadic function
	ft_update_tab(tab, 1);       // calculate special cases and length                      
	if (tab->wdt && !tab->dash)  // if width and not - flag
		ft_right_cs(tab, 0);     // handle right alignment
	tab->tl += write(1, &a, 1);  // print char
	if (tab->wdt && tab->dash)   // if width and - flag      
		ft_left_cs(tab, 0);      // handle left alignment                 
}

static int	ft_eval_format(t_print *tab, const char *restrict format, int i)
{
	/*%d, %i, %u, %f,F, %e,E, %g,G %x,X %o, %s, %c, %p, %a,A, %n
	if (format[i] == s)
		
	if (format[i] == d)

	if (format[i] == zu)*/



	while (format[i])
	{
		if (format[i] == '.')
		{
			tab->pnt = 1; // we set it to true, 1
			i++;
		}
		if (format[i] == '-')
		{
			tab->dash = 1;
			i++;
		}
	}
		if (format[i] == 'c')
			ft_print_char(tab);
		if (format[i] == 'd' || format[i] == 'i')
			ft_print_integer(tab);

	if (tab && format && i)
		return (i);
	else
		return (0);
}

static void	ft_initialise_tab(t_print *tab)
{
	int		index;

	index = 0;
	if (tab)
		index++;
}

int	ft_printf(const char *restrict format, ...)
{
	t_print *tab;
	int		i;
	int		ret;

	//printf("paska %d. %s \n", index, string);

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

int	main(int ac, char **argv)
{
	const char *restrict format;

	format = NULL;
	if (ac == 2)
	{
		format = argv[1];
		ft_printf(format);
		write(1, "\n", 1);
	}
	else
		usage(argv[0]);
	/*if (!format)
		ft_error();*/
	return (0);
}
