/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pile_is_empty_filo.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 13:13:12 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/14 13:13:32 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_pile_is_empty_filo(t_pile_filo *pile)
{
	if (pile == NULL)
		return (-1);
	return (pile->head == 0);
}
