/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 02:05:29 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/29 20:30:36 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void				parse_lights(t_json_value *l)
{
	t_json_array	*ar;
	unsigned long	i;

	if (l == NULL || l->type != array || (ar = (t_json_array*)l->ptr) == NULL ||
		(argn()->nb_lights = ar->nb_values) == 0 || ar->value == NULL ||
		(*lights() = (t_light*)ft_malloc(sizeof(t_light) * ar->nb_values))
		== NULL)
		return ;
	i = -1;
	while (++i < ar->nb_values)
		(*lights())[i] = (t_light){.position =
		cl_vector_from_json_array(ft_json_search_pair_in_object(ar->value[i],
		(t_json_string){.length = 8, .ptr = "position"}),
		(cl_float4){.x = 0, .y = 0, .z = 0, .w = 0}), .color =
		cl_vector_from_json_array(ft_json_search_pair_in_object(ar->value[i],
		(t_json_string){.length = 5, .ptr = "color"}),
		(cl_float4){.x = 1, .y = 1, .z = 1, .w = 0})};
}
