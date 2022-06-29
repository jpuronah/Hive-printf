/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 09:20:58 by jpuronah          #+#    #+#             */
/*   Updated: 2021/12/27 18:22:58 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	char	ch;
	size_t	len;

	str = (char *)s;
	ch = (char)c;
	len = ft_strlen(str);
	while (str[len] != c && len != 0)
		len--;
	if (str[len] != ch)
		return (NULL);
	if (str[len] == ch)
		str = (char *)(str + len);
	return (str);
}
