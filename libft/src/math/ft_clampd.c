/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clampd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 03:52:37 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/24 03:52:54 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

double				ft_clampd(double v, double min, double max)
{
	if (max < min)
		ft_swapd(&max, &min);
	if (v < min)
		return (min);
	if (v > max)
		return (max);
	return (v);
}
