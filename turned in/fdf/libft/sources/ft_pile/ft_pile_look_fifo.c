/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pile_look_fifo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 13:22:03 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/02 14:58:17 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** don't change data unless it is NULL
*/

t_pile_fifo	*ft_pile_look_fifo(t_pile_fifo *pile, void *data)
{
	if (pile == NULL)
		return (NULL);
	if (data == NULL)
		data = pile->data[pile->tail];
	return (pile);
}
