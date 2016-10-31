/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_projection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/24 20:40:25 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_vector		ft_vector_projection(const t_vector a, const t_vector b)
{
	t_vector	t;

	if (b.x == 0 && b.y == 0 && b.z == 0)
		t = b;
	else
		t = ft_vector_scale(b, (ft_vector_dot_product(a, b) /
										(b.x * b.x + b.y * b.y + b.z * b.z)));
	return (ft_vector_substract(a, t));
}
