/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_angle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/07 03:43:42 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

double			ft_vector_angle(const t_vector a, const t_vector b)
{
	double	vec_a_mag;

	vec_a_mag = ft_vector_magnitude(a);
	return (ft_acos(ft_vector_dot_product(a, b) / (vec_a_mag * vec_a_mag)));
}
