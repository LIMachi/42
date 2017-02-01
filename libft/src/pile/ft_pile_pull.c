/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pile_pull.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 13:17:30 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/27 16:45:40 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_pile	*ft_pile_pull(t_pile *pile, void **data)
{
	if (pile == NULL)
		return (NULL);
	if (pile->head == 0)
		return (NULL);
	if (data != NULL && *data == NULL)
		*data = pile->data[--pile->head];
	pile->data[pile->head + 1] = NULL;
	return (pile);
}
