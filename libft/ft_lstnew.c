/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:34:32 by jpuronah          #+#    #+#             */
/*   Updated: 2021/12/27 12:37:07 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list		*list;

	list = (t_list *)malloc(sizeof(t_list) * 1);
	if (!list)
		return (NULL);
	if (content && content_size)
	{
		list->content = (void *)malloc(sizeof(content) * content_size);
		if (!list->content)
			return (NULL);
		ft_memmove(list->content, content, content_size);
		list->content_size = (size_t)malloc(sizeof(content_size) * 1);
		if (!list->content_size)
			return (NULL);
		list->content_size = content_size;
	}
	if (!content)
	{
		list->content = NULL;
		list->content_size = 0;
	}
	list->next = NULL;
	return (list);
}
