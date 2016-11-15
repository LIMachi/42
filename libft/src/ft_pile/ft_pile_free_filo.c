/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pile_free_filo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 13:18:22 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/14 13:18:43 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void		ft_pile_free_filo(t_pile_filo *pile)
{
	if (pile == NULL)
		return ;
	if (pile->data != NULL)
		free(pile->data);
	free(pile);
}
