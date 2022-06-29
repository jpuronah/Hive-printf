/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_double.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 20:27:50 by jpuronah          #+#    #+#             */
/*   Updated: 2022/06/27 16:34:19 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static size_t	ft_len(int n)
{
	size_t	len;

	len = 0;
	if (n < 0)
	{
		n = n * -1;
		len++;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static char	*ft_str_null(char *str)
{
	str = (char *)malloc(sizeof(char) * 2);
	if (!str)
		return (NULL);
	str[0] = '0';
	str[1] = '\0';
	return (str);
}

static char	*ft_min_int(int nb)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * 12);
	if (!str)
		return (NULL);
	str[0] = '-';
	str[1] = '2';
	str[2] = '1';
	str[3] = '4';
	str[4] = '7';
	str[5] = '4';
	str[6] = '8';
	str[7] = '3';
	str[8] = '6';
	str[9] = '4';
	str[10] = '8';
	str[11] = '\0';
	if (nb)
		return (str);
	return (NULL);
}

char	*ft_get_string(char *str, int n, double d, t_printf *flags)
{
	size_t	i;
	int		precision;

	precision = flags->precision * 2;
	while (d != 0 && precision > 0 && n == 0)
	{
		d *= 10;
		precision--;
		if (precision == 0)
			n = round(d);
	}
	i = ft_len(n);
	if (n == 0)
		return (ft_str_null(str));
	if (n == -2147483648)
		return (ft_min_int(n));
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i--] = '\0';
	if (n < 0 && n != -2147483648)
	{
		str[0] = '-';
		n = -n;
	}
	while (n > 0)
	{
		str[i--] = (n % 10) + 48;
		n = n / 10;
	}
	return (str);
}

char	*ft_itoa_double(double dubbel, t_printf *flags)
{
	int		n;
	double	difference;
	char	*str1;
	char	*str2;

	n = (int)dubbel;
	difference = dubbel - (double)n;
	str1 = NULL;
	str1 = ft_get_string(str1, n, 0.0, flags);
	str2 = NULL;
	str2 = ft_get_string(str2, 0, difference, flags);
	if (str2)
	{
		str1 = ft_strjoin(str1, ".");
		str2 = ft_strjoin(str1, str2);
	}
	else
		str2 = ft_strdup(str1);
	free(str1);
	return (str2);
}
