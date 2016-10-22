/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pile_push_fifo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 13:21:22 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/14 14:50:14 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_pile_fifo	*ft_pile_push_fifo(t_pile_fifo *pile, void* data)
{
	if (pile == NULL)
		return (NULL);
	if (pile->data[pile->head + 1] != NULL)
		return (NULL);
	pile->data[pile->head++] = data;
	if (pile->head == pile->size)
		pile->head = 0;
	if (pile->head == pile->tail)
		return (NULL);
	return (pile);
}
