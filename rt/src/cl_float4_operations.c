/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_float4_operations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 08:19:36 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/30 15:46:50 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

cl_float4	cl_float4_normalize(cl_float4 v)
{
	cl_float	t;

	if ((v.x == 0.0f && v.y == 0.0f && v.z == 0.0f) ||
		(t = (v.x * v.x + v.y * v.y + v.z * v.z)) == 1.0f)
		return (v);
	return (cl_float4_scale(v, 1.0f / ft_sqrtf(t)));
}

cl_float4	cl_float4_add(cl_float4 a, cl_float4 b)
{
	return ((cl_float4){
		.x = a.x + b.x, .y = a.y + b.y, .z = a.z + b.z, .w = a.w + b.w});
}

void		cl_float4_p_add(cl_float4 *a, cl_float4 b)
{
	a->x += b.x;
	a->y += b.y;
	a->z += b.z;
	a->w += b.w;
}

cl_float4	cl_float4_scale(cl_float4 v, cl_float s)
{
	return ((cl_float4){
		.x = v.x * s, .y = v.y * s, .z = v.z * s, .w = v.w * s});
}

cl_float4	cl_float4_sub(cl_float4 a, cl_float4 b)
{
	return ((cl_float4){
		.x = a.x - b.x, .y = a.y - b.y, .z = a.z - b.z, .w = a.w - b.w});
}
