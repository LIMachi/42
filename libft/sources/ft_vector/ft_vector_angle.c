/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_angle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/24 21:22:47 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

double			ft_vector_angle(const t_vector a, const t_vector b)
{
	double	vec_a_mag;

	vec_a_mag = ft_vector_magnitude(a);
	if (vec_a_mag == 0)
		return (INFINITY);
	return (ft_acos(ft_vector_dot_product(a, b) / (vec_a_mag * vec_a_mag)));
}
