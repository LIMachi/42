/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 14:53:46 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/27 14:54:17 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

cl_float4	*ray_plane(const t_camera *cam, const cl_int2 screen_size)
{
	t_vector	vpul;
	cl_int2		i;
	cl_float4	*out;

	vpul.x = cam->pos.x + (cam->dir.x * cam->dist) + (cam->up.x * (
			screen_size.y / 2.0)) - (cam->right.x * (screen_size.x / 2.0));
	vpul.y = cam->pos.y + (cam->dir.y * cam->dist) + (cam->up.y * (
			screen_size.y / 2.0)) - (cam->right.y * (screen_size.x / 2.0));
	vpul.z = cam->pos.z + (cam->dir.z * cam->dist) + (cam->up.z * (
			screen_size.y / 2.0)) - (cam->right.z * (screen_size.x / 2.0));
	i.y = -1;
	if ((out = (cl_float4*)ft_malloc(sizeof(
			cl_float4) * screen_size.x * screen_size.y)) == NULL)
		return (NULL);
	while (++i.y < screen_size.y && (i.x = -1))
		while (++i.x < screen_size.x)
			out[i.y * screen_size.x + i.x] = (cl_float4){
				.x = (cl_float)(vpul.x + cam->right.x * i.x - cam->up.x * i.y),
				.y = (cl_float)(vpul.y + cam->right.y * i.x - cam->up.y * i.y),
				.z = (cl_float)(vpul.z + cam->right.z * i.x - cam->up.z * i.y),
				.w = 0};
	return (out);
}
