/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pile_push.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 13:13:54 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/18 12:41:28 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_pile	*ft_pile_push(t_pile *pile, void *data)
{
	if (pile == NULL)
		return (NULL);
	if (pile->head == pile->size)
		return (NULL);
	if (pile->data[pile->head + 1] != NULL)
		return (NULL);
	pile->data[pile->head++] = data;
	return (pile);
}
