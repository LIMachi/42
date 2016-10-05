/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pt3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/15 08:52:13 by hmartzol          #+#    #+#             */
/*   Updated: 2016/07/15 08:52:30 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_point3d	ft_pt3add(t_point3d a, t_point3d b)
{
	return ((t_point3d){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_point3d	ft_pt3sub(t_point3d a, t_point3d b)
{
	return ((t_point3d){a.x - b.x, a.y - b.y, a.z - b.z});
}
