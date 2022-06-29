/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 15:01:20 by jpuronah          #+#    #+#             */
/*   Updated: 2021/12/19 20:42:35 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
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
			array[i] = (*f)(i, s[i]);
			i++;
		}
	}
	array[i] = '\0';
	return (array);
}
