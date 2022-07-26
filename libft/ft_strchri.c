/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchri.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 11:58:36 by jpuronah          #+#    #+#             */
/*   Updated: 2022/07/26 11:58:52 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
