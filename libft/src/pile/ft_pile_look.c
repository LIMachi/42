/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pile_look.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 13:15:55 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/27 16:45:10 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** don't change data unless it is NULL
*/

t_pile	*ft_pile_look(t_pile *pile, void **data)
{
	if (pile == NULL)
		return (NULL);
	if (pile->head == 0)
		return (NULL);
	if (data != NULL && *data == NULL)
		*data = pile->data[pile->head - 1];
	return (pile);
}
