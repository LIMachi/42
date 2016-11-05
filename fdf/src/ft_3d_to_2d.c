/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3d_to_2d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 16:13:33 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/01 16:13:45 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_point	ft_3d_to_2d(t_vector focal, t_point screen_center, t_vector vertex)
{
	double tmp;

	if (focal.z + vertex.z > -0.001 && focal.z + vertex.z < 0.001)
		return (ft_point(0x7FFFFFFF, 0x7FFFFFFF));
	tmp = focal.z / (focal.z + vertex.z);
	return (ft_point(vertex.x * tmp + screen_center.x,
				vertex.y * tmp + screen_center.y));
}
