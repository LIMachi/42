/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clampi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 03:53:05 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/24 03:53:19 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int					ft_clampi(int v, int min, int max)
{
	if (max < min)
		ft_swapi(&max, &min);
	if (v < min)
		return (min);
	if (v > max)
		return (max);
	return (v);
}
