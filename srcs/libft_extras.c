/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_extras.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:44:22 by jpuronah          #+#    #+#             */
/*   Updated: 2022/07/21 14:45:33 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

double	ft_pow(double n, int pow)
{
	if (pow)
		return (n * ft_pow(n, pow - 1));
	else
		return (1);
}

int	ft_islower(int c)
{
	if ((c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}

int	ft_isupper(int c)
{
	if ((c >= 65 && c <= 90))
		return (1);
	else
		return (0);
}

long long	ft_abs_ll(long long i)
{
	if (i < 0)
		return (i * -1);
	return (i);
}

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

int	ft_strchri(char *s, int c, int index)
{
	char	*str;
	char	ch;
	int		ret;

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

int	ft_strchri_lu(char *s, int c, int index)
{
	char	*str;
	char	ch;
	int		ret;

	printf("c: %c\n", c);
	printf("s: %s\n", s);
	str = (char *)s;
	ch = (char)c;
	ret = -1;
	while (str[index] != '\0')
	{
		if (str[index] == ch || str[index] == ch + 32)
			ret = index;
		index++;
	}
	printf("retlu: %d\n", ret);
	printf("str[i]: %c\n", str[index - 1]);
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

char	*ft_strdupi(char const *s1, size_t size)
{
	char			*dest;
	unsigned int	len;
	unsigned int	i;

	len = 0;
	while (s1[len] != '\0')
		len++;
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (s1[i] != '\0' && size--)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
