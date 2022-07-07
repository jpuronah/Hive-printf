/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 15:12:36 by jpuronah          #+#    #+#             */
/*   Updated: 2021/12/19 21:13:41 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strequ(char const *s1, char const *s2)
{
	size_t	i;

	i = 0;
	if (s1 && s2)
	{
		while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
			i++;
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return (0);
	}
	return (1);
}
