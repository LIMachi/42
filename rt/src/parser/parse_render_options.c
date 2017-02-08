/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_render_options.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 01:56:45 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/30 15:30:33 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void				parse_render_options_0(t_json_value *ro)
{
	t_json_value		*v[2];
	t_json_value_type	*la_norm_est_chiante;

	v[0] = ft_json_search_pair_in_object(ro,
		(t_json_string){.length = 4, .ptr = "size"});
	la_norm_est_chiante = (t_json_value_type[2]){integer, integer};
	ft_json_check_array_types(v[0], 2, la_norm_est_chiante) ?
		(void)(argn()->screen_size = (cl_int2){.x =
		(cl_int) * (int*)((t_json_array*)v[0]->ptr)->value[0]->ptr, .y =
		(cl_int) * (int*)((t_json_array*)v[0]->ptr)->value[1]->ptr}) : 0;
	v[0] = ft_json_search_pair_in_object(ro,
		(t_json_string){.length = 8, .ptr = "lighting"});
	v[1] = ft_json_search_pair_in_object(v[0],
		(t_json_string){.length = 7, .ptr = "ambient"});
	argn()->ambient = (v[1] != NULL && v[1]->type == number ?
		ft_clampd(*(double*)v[1]->ptr, 0.0, 1.0) : 0.05f);
	v[1] = ft_json_search_pair_in_object(v[0],
		(t_json_string){.length = 6, .ptr = "direct"});
	argn()->direct = (v[1] != NULL && v[1]->type == number ?
		ft_clampd(*(double*)v[1]->ptr, 0.0, 1.0) : 0.0f);
}

void				parse_render_options(t_json_value *ro)
{
	t_json_value	*v;

	parse_render_options_0(ro);
	v = ft_json_search_pair_in_object(ro,
		(t_json_string){.length = 9, .ptr = "antialias"});
	argn()->antialias = (v != NULL && v->type == integer ?
		ft_clampi(*(int*)v->ptr, 1, 16) : 1);
	v = ft_json_search_pair_in_object(ro,
		(t_json_string){.length = 12, .ptr = "bounce_depth"});
	argn()->bounce_depth = (v != NULL && v->type == integer ?
		ft_clampi(*(int*)v->ptr, 1, 32) : 1);
	v = ft_json_search_pair_in_object(ro,
		(t_json_string){.length = 6, .ptr = "filter"});
	argn()->filter = ft_json_check_string(v, 4,
		(char**)(size_t[4]){(size_t)NULL, (size_t)"sepia", (size_t)"grayscale",
			(size_t)"cartoon"}, argn()->filter);
	v = ft_json_search_pair_in_object(ro,
		(t_json_string){.length = 11, .ptr = "stereoscopy"});
	argn()->stereoscopy = (v != NULL && v->type == boolean ?
		*(int*)v->ptr : 0);
	v = ft_json_search_pair_in_object(ro,
		(t_json_string){.length = 6, .ptr = "skybox"});
	argn()->skybox = parse_texture(v, argn()->skybox);
}
