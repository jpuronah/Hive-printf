/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:49:02 by jpuronah          #+#    #+#             */
/*   Updated: 2022/04/14 14:11:08 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;

	if (lst != NULL && f != NULL)
	{
		new = (*f)(lst);
		if (new != NULL && lst->next != NULL)
			new->next = ft_lstmap((lst->next), (*f));
		return (new);
	}
	return (NULL);
}
