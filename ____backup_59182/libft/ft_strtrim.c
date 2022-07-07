/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 23:20:43 by jpuronah          #+#    #+#             */
/*   Updated: 2021/12/27 18:28:24 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_whitespace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}

static int	ft_is_char(char const *s)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		if (!(ft_is_whitespace(s[i])))
			return (1);
		s++;
	}
	return (0);
}

static size_t	ft_end(char const *s)
{
	size_t	i;
	size_t	end;

	i = ft_strlen(s) - 1;
	end = 0;
	while (ft_is_whitespace(s[i]))
		i--;
	if (!(ft_is_whitespace(s[i])))
		end = i;
	if (end)
		return (end);
	else
		return (0);
}

char	*ft_strtrim(char const *s)
{
	unsigned int	start;
	size_t			end;
	size_t			len;
	char			*str;

	start = 0;
	if (!s)
		return (NULL);
	if (!(ft_is_char(s)))
	{
		str = ft_strnew(1);
		return (str);
	}
	while (ft_is_whitespace(s[start]))
		start++;
	end = ft_end(s);
	len = end - start + 1;
	str = ft_strsub(s, start, len);
	return (str);
}
