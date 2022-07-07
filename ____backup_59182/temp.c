
void		parse_optionals(t_printf *p)
{
	p->f = 0;
	p->min_length = 0;
	p->precision = 1;
	parse_flags(p);
	field_width_precision(p);
	while (42)
	{
		if (*p->format == 'l')
			p->f |= (p->format[1] == 'l' && ++p->format) ? F_LONG2 : F_LONG;
		else if (*p->format == 'h')
			p->f |= (p->format[1] == 'h' && ++p->format) ? F_SHORT2 : F_SHORT;
		else if (*p->format == 'j')
			p->f |= F_INTMAX;
		else if (*p->format == 'z')
			p->f |= F_SIZE_T;
		else
			break ;
		++p->format;
	}
	parse_flags(p);
	(p->f & F_PLUS) ? p->f &= ~F_SPACE : 0;
	if (ft_strchr("CDSUOBX", *p->format))
		p->f |= (*p->format != 'X') ? F_LONG : F_UPCASE;
	conversion_specifier(p);
}



static void	conversion_specifier(t_printf *p)
{
	p->c = *p->format;
	if (p->c == 's')
		(p->f & F_LONG || p->f & F_LONG2) ? pf_putwstr(p) : pf_putstr(p);
	else if (ft_strchr("dDi", p->c))
		pf_putnb(p);
	else if (p->c == 'f' || p->c == 'F')
		(p->f & F_APP_PRECI && !p->precision) ? pf_putnb(p) : pf_putdouble(p);
	else if (p->c == 'c' || p->c == 'C')
		pf_character(p, va_arg(p->ap, unsigned));
	else if (ft_strchr("oOuUbBxX", p->c))
		pf_putnb_base(ft_strchri_lu(".b..ou..x", p->c, -1) << 1, p);
	else if (p->c == 'S')
		pf_putwstr(p);
	else if (p->c == 'p')
		print_pointer_address(p);
	else if (p->c == 'n')
		*va_arg(p->ap, int *) = p->len;
	else if (p->c == 'm')
		ft_printf_putstr(STRERR(errno), p);
	else if (p->c == '{')
		color(p);
	else
		cs_not_found(p);
}


void	pf_putstr(t_printf *p)
{
	unsigned	*s;
	int			len;

	if (!(s = va_arg(p->ap, unsigned*)))
		ft_printf_putstr((char *)s, p);
	else
	{
		len = (int)(ft_strlen((char*)s));
		(p->f & F_APP_PRECI) ? len = MIN(p->precision, len) : 0;
		p->padding = (p->min_length - len) > 0 ? (p->min_length - len) : 0;
		padding(p, 0);
		buffer(p, s, len);
		padding(p, 1);
	}
}


void	padding(t_printf *p, int n)
{
	if (!p->padding)
		return ;
	p->c = 32 | (p->f & F_ZERO);
	if (!n && !(p->f & F_MINUS))
		while (p->padding--)
			buffer(p, &p->c, 1);
	else if (n && (p->f & F_MINUS))
		while (p->padding--)
			buffer(p, &p->c, 1);
}

void	pf_character(t_printf *p, unsigned c)
{
	p->printed = (p->f & F_LONG || p->f & F_LONG2) ? ft_wcharlen(c) : 1;
	if ((p->padding = p->min_length - p->printed) < 0)
		p->padding = 0;
	padding(p, 0);
	pf_putwchar(p, c, p->printed, p->printed);
	padding(p, 1);
}

	char	*string;
	int		index;

	index = 0;
	string = va_arg(flags->args, char *);
	if (!string)
		print_null_string(string, flags);
	flags->wordlen = ft_strlen(string);
	if ((flags->wordlen - flags->precision) > 0)
		flags->padding = (flags->length - flags->wordlen);
	else
		flags->padding = 0;
	padding(flags, 0);
	while (string[index])
		flags->total_length += write(1, &string[index++], 1);
	padding(flags, 1);