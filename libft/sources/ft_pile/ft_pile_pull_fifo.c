/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pile_pull_fifo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 13:22:35 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/02 14:58:18 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_pile_fifo	*ft_pile_pull_fifo(t_pile_fifo *pile, void *data)
{
	if (pile == NULL)
		return (NULL);
	if (pile->head == 0)
		return (NULL);
	if (pile->head == pile->tail)
		return (NULL);
	if (data == NULL)
		data = pile->data[pile->tail++];
	pile->data[pile->tail - 1] = NULL;
	if (pile->tail == pile->size)
		pile->tail = 0;
	return (pile);
}
