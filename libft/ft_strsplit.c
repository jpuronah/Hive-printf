/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 13:53:10 by jpuronah          #+#    #+#             */
/*   Updated: 2021/12/27 18:37:25 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_wordlen(char const *s, char c)
{
	size_t	wordlen;

	wordlen = 0;
	while (*s != c && *s)
	{
		wordlen++;
		s++;
	}
	return (wordlen);
}

static size_t	ft_wordcount(char const *s, char c)
{
	size_t	wordcount;

	wordcount = 0;
	if (!s || !c)
		return (0);
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			while (*s != c && (*s != '\0'))
				s++;
			wordcount++;
		}
	}
	return (wordcount);
}

static char	**ft_free_array(char **arr, size_t i)
{
	while (arr[i])
	{
		free(arr[i]);
		i--;
	}
	ft_strdel(arr);
	return (arr);
}

static char	**ft_split(const char *s, char c, char **array)
{
	size_t	wordlen;
	size_t	i;
	size_t	j;
	int		k;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			wordlen = ft_wordlen(s + i, c);
			array[j] = (char *)malloc(sizeof(char) * (wordlen + 1));
			if (!array[j])
				return (ft_free_array(array, j - 1));
			k = 0;
			while (wordlen-- > 0)
				array[j][k++] = s[i++];
			array[j++][k] = '\0';
		}
	}
	array[j] = NULL;
	return (array);
}

char	**ft_strsplit(char const *s, char c)
{
	size_t	wordcount;
	char	**array;

	if (s && c)
	{
		wordcount = ft_wordcount(s, c);
		array = (char **)malloc((wordcount + 1) * sizeof(char *));
		if (!array)
			return (NULL);
		array = ft_split(s, c, array);
		return (array);
	}
	else
		return (NULL);
}
