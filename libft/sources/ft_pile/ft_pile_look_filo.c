/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pile_look_filo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 13:15:55 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/14 14:48:55 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_pile_filo	*ft_pile_look_filo(t_pile_filo *pile, void* data)
{
	if (pile == NULL)
		return (NULL);
	//if (data != NULL) warning
	(void)data;
	data = pile->data[pile->head];
	return (pile);
}
