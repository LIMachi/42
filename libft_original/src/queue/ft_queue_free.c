/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 13:23:22 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/18 12:42:32 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_queue_free(t_queue *queue)
{
	if (queue == NULL)
		return ;
	if (queue->data != NULL)
		ft_free(queue->data);
	ft_free(queue);
}
