/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_in_frustrum.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 16:41:02 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/01 17:11:44 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftx.h>

int				ft_is_in_frustrum(t_frustrum frustrum, t_vector vertex)
{
	t_vector	tmp1;
	t_vector	tmp2;
	int			i;

	tmp1 = ft_vector_from_a_to_b(frustrum.near_point, frustrum.near_normal);
	tmp2 = ft_vector_from_a_to_b(frustrum.near_point, vertex);
	i = ft_vector_dot_product(tmp1, tmp2) > 0;
	tmp1 = ft_vector_from_a_to_b(frustrum.far_point, frustrum.far_normal);
	tmp2 = ft_vector_from_a_to_b(frustrum.far_point, vertex);
	i &= ft_vector_dot_product(tmp1, tmp2) > 0;
	tmp1 = ft_vector_from_a_to_b(frustrum.top_point, frustrum.top_normal);
	tmp2 = ft_vector_from_a_to_b(frustrum.top_point, vertex);
	i &= ft_vector_dot_product(tmp1, tmp2) > 0;
	tmp1 = ft_vector_from_a_to_b(frustrum.bottom_point, frustrum.bottom_normal);
	tmp2 = ft_vector_from_a_to_b(frustrum.bottom_point, vertex);
	i &= ft_vector_dot_product(tmp1, tmp2) > 0;
	tmp1 = ft_vector_from_a_to_b(frustrum.right_point, frustrum.right_normal);
	tmp2 = ft_vector_from_a_to_b(frustrum.right_point, vertex);
	i &= ft_vector_dot_product(tmp1, tmp2) > 0;
	tmp1 = ft_vector_from_a_to_b(frustrum.left_point, frustrum.left_normal);
	tmp2 = ft_vector_from_a_to_b(frustrum.left_point, vertex);
	i &= ft_vector_dot_product(tmp1, tmp2) > 0;
	return (i);
}
