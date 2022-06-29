/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countwords.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 16:35:07 by jpuronah          #+#    #+#             */
/*   Updated: 2022/05/19 15:54:19 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_countwords(char *string, char seperator)
{
	size_t	result;
	size_t	index;

	index = 0;
	result = 0;
	while (string[index] && string[index] == seperator)
		index++;
	while (string[index])
	{
		while (string[index] && string[index] != seperator)
			index++;
		result++;
		while (string[index] && string[index] == seperator)
			index++;
	}
	return (result);
}
