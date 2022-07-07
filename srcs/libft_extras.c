/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_extras.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:44:22 by jpuronah          #+#    #+#             */
/*   Updated: 2022/07/07 13:48:00 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	ft_strchri(const char *s, int c, int index)
{
	char	*str;
	char	ch;
	char	ret;

	str = (char *)s;
	ch = (char)c;
	ret = -1;
	while (str[index] != '\0')
	{
		if (str[index] == ch)
			ret = index;
		index++;
	}
	if (ret > -1)
		return (ret);
	return (-1);
}


static size_t	ft_len(long long n)
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

char	*ft_itoa_long_long(long long n)
{
	size_t	i;
	char	*str;

	i = ft_len(n);
	str = NULL;
	if (n == 0)
		return (ft_str_null(str));
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
