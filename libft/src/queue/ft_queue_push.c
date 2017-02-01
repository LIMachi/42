/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue_push.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 13:21:22 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/18 12:42:39 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_queue	*ft_queue_push(t_queue *queue, void *data)
{
	if (queue == NULL)
		return (NULL);
	if (queue->data[queue->head + 1] != NULL)
		return (NULL);
	queue->data[queue->head++] = data;
	if (queue->head == queue->size)
		queue->head = 0;
	if (queue->head == queue->tail)
		return (NULL);
	return (queue);
}
