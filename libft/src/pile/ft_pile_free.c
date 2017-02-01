/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pile_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 13:18:22 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/18 12:41:19 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void		ft_pile_free(t_pile *pile)
{
	if (pile == NULL)
		return ;
	if (pile->data != NULL)
		ft_free(pile->data);
	ft_free(pile);
}
