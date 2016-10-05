/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_point3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 18:15:00 by hmartzol          #+#    #+#             */
/*   Updated: 2016/02/18 18:16:12 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_point3d	ft_point3d(double x, double y, double z)
{
	t_point3d out;

	out.x = x;
	out.y = y;
	out.z = z;
	return (out);
}
