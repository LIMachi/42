/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue_pull.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 13:22:35 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/27 16:46:28 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_queue	*ft_queue_pull(t_queue *queue, void **data)
{
	if (queue == NULL)
		return (NULL);
	if (queue->head == 0)
		return (NULL);
	if (queue->head == queue->tail)
		return (NULL);
	if (data != NULL && *data == NULL)
		*data = queue->data[queue->tail++];
	queue->data[queue->tail - 1] = NULL;
	if (queue->tail == queue->size)
		queue->tail = 0;
	return (queue);
}
