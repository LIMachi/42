/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 14:37:45 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/27 08:43:44 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_camera	*cam(void)
{
	static t_camera	cam = {

	.pos = {.x = 0, .y = 0, .z = 0, .w = 0},
	.dir = {.x = 0, .y = 0, .z = 1, .w = 0},
	.up = {.x = 0, .y = 1, .z = 0, .w = 0},
	.right = {.x = 1, .y = 0, .z = 0, .w = 0},
	.vpul = {.x = 0, .y = 0, .z = 0, .w = 0},
	.vp_size = {.x = 0, .y = 0},
	.dist = 0,
	.orientation = {.r = 1, .i = 0, .j = 0, .k = 0}};
	return (&cam);
}

void		calc_vpul(void)
{
	float	y;
	float	x;

	y = ((float)cam()->vp_size.y / 2.0f);
	x = -((float)cam()->vp_size.x / 2.0f);
	cam()->vpul.x = ((cam()->dir.x * cam()->dist) +
			(cam()->up.x * y)) + (cam()->right.x * x);
	cam()->vpul.y = ((cam()->dir.y * cam()->dist) +
			(cam()->up.y * y)) + (cam()->right.y * x);
	cam()->vpul.z = ((cam()->dir.z * cam()->dist) +
			(cam()->up.z * y)) + (cam()->right.z * x);
	cam()->vpul.w = 0.0f;
}

t_vector	cl_float4_to_vector(cl_float4 v)
{
	return ((t_vector){.x = v.x, .y = v.y, .z = v.z});
}

cl_float4	vector_to_cl_float4(t_vector v)
{
	return ((cl_float4){.x = v.x, .y = v.y, .z = v.z, .w = 0.0f});
}

void		rotate_cam(double angle, t_vector axe)
{
	t_quaternion	q;
	t_matrix		*mat;
	t_vector		*tva;

	q = ft_quat_rotation_build(angle, axe);
	q = ft_quat_multiply(cam()->orientation, q);
	cam()->orientation = q;
	mat = ft_quat_rotation_to_matrix(NULL, q);
	tva = ft_matrix_multply_vector_array((t_vector[3]) {
			cam()->origin_dir,
			cam()->origin_up,
			cam()->origin_right}, 3, mat);
	cam()->dir = vector_to_cl_float4(tva[0]);
	cam()->up = vector_to_cl_float4(tva[1]);
	cam()->right = vector_to_cl_float4(tva[2]);
	ft_matrix_free(mat);
	calc_vpul();
}
