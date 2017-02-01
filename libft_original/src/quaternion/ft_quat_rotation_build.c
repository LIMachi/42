/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quat_rotation_build.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 0000/00/00 00:00:00 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/18 23:52:52 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** Normalize the vector if needed, math and logic optimised by me.
** Return -42 in the r component if an error (null vector) occur
*/

t_quaternion			ft_quat_rotation_build(double angle,
												const t_vector vector)
{
	double			t;
	t_quaternion	out;

	if (vector.x == vector.y && vector.x == vector.z && vector.x == 0)
		return ((t_quaternion){.r = -42});
	angle /= 2;
	out.r = ft_cos(angle);
	if ((t = vector.x * vector.x + vector.y * vector.y + vector.z * vector.z)
																		!= 1)
		t = ft_sin(angle) / ft_sqrtd(t);
	else
		t = ft_sin(angle);
	out.i = t * vector.x;
	out.j = t * vector.y;
	out.k = t * vector.z;
	return (out);
}
