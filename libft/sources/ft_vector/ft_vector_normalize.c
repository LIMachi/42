/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_normalize.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/24 20:37:52 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_vector		ft_vector_normalize(const t_vector v)
{
	double t;

	if (v.x == 0 && v.y == 0 && v.z == 0)
		return (v);
	if ((t = v.x * v.x + v.y * v.y + v.z * v.z) != 1)
		return (ft_vector_scale(v, 1 / ft_sqrtd(t)));
	return (v);
}
