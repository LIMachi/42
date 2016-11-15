/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pile_new_fifo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 12:33:13 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/14 13:23:42 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_pile_fifo	*ft_pile_new_fifo(unsigned int size)
{
	t_pile_fifo	*out;

	if (size == 0)
		return (NULL);
	if ((out = (t_pile_fifo*)malloc(sizeof(t_pile_fifo))) == NULL)
		return (NULL);
	if ((out->data = (void**)malloc(sizeof(void*) * size)) == NULL)
		return (NULL);
	out->size = size;
	out->head = 0;
	out->tail = 0;
	return (out);
}
