/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_number_length.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 10:46:50 by jpuronah          #+#    #+#             */
/*   Updated: 2022/10/18 10:46:54 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_number_length(long long number)
{
	int	i;

	i = 1;
	if (number < 0)
	{
		number *= -1;
		i++;
	}
	while (number >= 10)
	{
		number /= 10;
		i++;
	}
	return (i);
}
