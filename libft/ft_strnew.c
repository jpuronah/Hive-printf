/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 14:39:08 by jpuronah          #+#    #+#             */
/*   Updated: 2022/02/18 23:36:05 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	size_t	i;
	char	*string;

	string = ft_memalloc(size + 1);
	if (!string)
		return (NULL);
	i = 0;
	while (i < size)
		string[i++] = '\0';
	return (string);
}
