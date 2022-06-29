/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_elem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:10:25 by jpuronah          #+#    #+#             */
/*   Updated: 2022/05/17 15:21:00 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_create_elem(void *data)
{
	t_list	*tmp;

	tmp = (void *)malloc(sizeof(t_list));
	if (!tmp)
		return (NULL);
	tmp->content = data;
	tmp->next = NULL;
	return (tmp);
}
