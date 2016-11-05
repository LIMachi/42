/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pile_pull_filo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 13:17:30 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/02 14:58:19 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_pile_filo	*ft_pile_pull_filo(t_pile_filo *pile, void *data)
{
	if (pile == NULL)
		return (NULL);
	if (pile->head == 0)
		return (NULL);
	if (data == NULL)
		data = pile->data[--pile->head];
	pile->data[pile->head + 1] = NULL;
	return (pile);
}
