/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pile_free_fifo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 13:23:22 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/14 13:23:45 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void		ft_pile_free_fifo(t_pile_fifo *pile)
{
	if (pile == NULL)
		return ;
	if (pile->data != NULL)
		free(pile->data);
	free(pile);
}
