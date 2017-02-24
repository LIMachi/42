/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_thales.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 00:02:06 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/30 15:21:01 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <rt.h>

cl_float	ft_float4_distance(cl_float4 v)
{
	return ((cl_float)ft_sqrtd(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w));
}

cl_float4	ft_vector_thales(cl_float4 origin, cl_float4 v1, cl_float4 v2,
		cl_float4 r)
{
	cl_float		tmp;

	(void)origin;
	if ((tmp = ft_float4_distance(v1)) == 0.0)
		return ((cl_float4){.x=0.0f, .y = 0.0f, .z = 0.0f, .w = 0.0f});
	return (cl_float4_scale(r, ft_float4_distance(v2) / tmp));
}
