/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pile_push_filo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 13:13:54 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/02 14:57:55 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_pile_filo	*ft_pile_push_filo(t_pile_filo *pile, void *data)
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
