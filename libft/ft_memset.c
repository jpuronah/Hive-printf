/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 11:47:09 by jpuronah          #+#    #+#             */
/*   Updated: 2021/12/27 18:41:43 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*new_b;
	size_t			i;

	new_b = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		*new_b = (unsigned char)c;
		new_b++;
		i++;
	}
	return (b);
}
