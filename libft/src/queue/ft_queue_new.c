/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 12:33:13 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/18 23:53:58 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_queue	*ft_queue_new(unsigned int size)
{
	t_queue	*out;

	if (size == 0)
		return (NULL);
	if ((out = (t_queue*)ft_malloc(sizeof(t_queue))) == NULL)
		return (NULL);
	if ((out->data = (void**)ft_malloc(sizeof(void*) * size)) == NULL)
		return (NULL);
	out->size = size;
	out->head = 0;
	out->tail = 0;
	return (out);
}
