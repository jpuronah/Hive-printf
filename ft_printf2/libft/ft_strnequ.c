/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 15:19:58 by jpuronah          #+#    #+#             */
/*   Updated: 2021/12/11 12:56:10 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	if (s1 && s2)
	{
		while ((i < n - 1) && s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
			i++;
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return (0);
	}
	return (1);
}
