/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 01:59:11 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/29 01:11:58 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void				parse_camera_1(void)
{
	cl_float4	t;

	t = cam()->dir;
	cam()->origin_dir = ft_vector(t.x, t.y, t.z);
	t = cam()->up;
	cam()->origin_up = ft_vector(t.x, t.y, t.z);
	t = cam()->right;
	cam()->origin_right = ft_vector(t.x, t.y, t.z);
}

void				parse_camera_0(t_json_value *vps)
{
	t_json_value_type	*j_ai_plus_d_idee_pour_railler_la_norme;

	j_ai_plus_d_idee_pour_railler_la_norme =
		(t_json_value_type[2]){integer | number, integer | number};
	if (ft_json_check_array_types(vps, 2,
			j_ai_plus_d_idee_pour_railler_la_norme))
	{
		cam()->vp_size.x = ((t_json_array*)vps->ptr)->value[0]->type == integer
			? (cl_float) * (int*)((t_json_array*)vps->ptr)->value[0]->ptr :
			(cl_float) * (double*)((t_json_array*)vps->ptr)->value[0]->ptr;
		cam()->vp_size.y = ((t_json_array*)vps->ptr)->value[1]->type == integer
			? (cl_float) * (int*)((t_json_array*)vps->ptr)->value[1]->ptr :
			(cl_float) * (double*)((t_json_array*)vps->ptr)->value[1]->ptr;
	}
}

void				parse_camera(t_json_value *c)
{
	t_json_value		*v;

	v = ft_json_search_pair_in_object(c,
		(t_json_string){.length = 8, .ptr = "position"});
	cam()->pos = cl_vector_from_json_array(v, cam()->pos);
	v = ft_json_search_pair_in_object(c,
		(t_json_string){.length = 9, .ptr = "direction"});
	cam()->dir = cl_vector_from_json_array(v, cam()->dir);
	v = ft_json_search_pair_in_object(c,
		(t_json_string){.length = 2, .ptr = "up"});
	cam()->up = cl_vector_from_json_array(v, cam()->up);
	v = ft_json_search_pair_in_object(c,
		(t_json_string){.length = 5, .ptr = "right"});
	cam()->right = cl_vector_from_json_array(v, cam()->right);
	v = ft_json_search_pair_in_object(c,
		(t_json_string){.length = 7, .ptr = "vp_size"});
	parse_camera_0(v);
	v = ft_json_search_pair_in_object(c,
		(t_json_string){.length = 4, .ptr = "dist"});
	if (v != NULL && (v->type == number || v->type == integer) &&
			v->ptr != NULL)
		cam()->dist = (v->type == number) ?
			(cl_float) * (double*)v->ptr : (cl_float) * (int*)v->ptr;
	parse_camera_1();
}
