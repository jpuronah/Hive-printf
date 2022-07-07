/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 14:53:37 by jpuronah          #+#    #+#             */
/*   Updated: 2021/12/19 20:42:27 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	unsigned int	i;
	char			*array;

	if (!s || !f)
		return (NULL);
	array = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!array)
		return (NULL);
	i = 0;
	if (s && f)
	{
		while (s[i])
		{
			array[i] = f(s[i]);
			i++;
		}
	}
	array[i] = '\0';
	return (array);
}
