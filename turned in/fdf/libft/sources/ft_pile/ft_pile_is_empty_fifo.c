/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pile_is_empty_fifo.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 13:20:55 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/14 13:21:03 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_pile_is_empty_fifo(t_pile_fifo *pile)
{
	if (pile == NULL)
		return (-1);
	return (pile->head == pile->tail);
}
