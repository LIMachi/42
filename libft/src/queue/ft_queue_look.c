/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue_look.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 13:22:03 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/27 16:46:46 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** don't change data unless it is NULL
*/

t_queue	*ft_queu_look(t_queue *queue, void **data)
{
	if (queue == NULL)
		return (NULL);
	if (data != NULL && *data == NULL)
		data = queue->data[queue->tail];
	return (queue);
}
