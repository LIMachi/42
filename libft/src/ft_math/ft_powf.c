/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_powf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 16:48:33 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/09 16:50:22 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

float	ft_powf(float nbr, int exp)
{
	float	out;

	out = 1.0f;
	while (exp > 0 && --exp)
		out *= nbr;
	while (exp < 0 && ++exp)
		out /= nbr;
	return (out);
}
