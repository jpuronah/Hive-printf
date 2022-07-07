/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:40:55 by jpuronah          #+#    #+#             */
/*   Updated: 2021/12/11 12:08:02 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*list;
	t_list	*nextlist;

	list = *alst;
	if (!del)
		return ;
	while (list)
	{
		nextlist = list->next;
		(del)(list->content, list->content_size);
		free(list);
		list = nextlist;
	}
	*alst = NULL;
}
