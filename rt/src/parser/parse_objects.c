/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 02:02:23 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/30 14:35:42 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include <rt.h>

cl_uint				parse_object_material(t_json_value *o)
{
	int	i;

	if (o == NULL || o->ptr == NULL)
		return (0);
	if (o->type == object)
	{
		materials()->materials = ft_reallocf(materials()->materials,
			sizeof(t_material) * materials()->nb_materials,
			sizeof(t_material) * (materials()->nb_materials + 1));
		materials()->name = ft_reallocf(materials()->name,
			sizeof(char *) * materials()->nb_materials,
			sizeof(char *) * (materials()->nb_materials + 1));
		materials()->name[materials()->nb_materials] = NULL;
		materials()->materials[materials()->nb_materials] =
			parse_material(o, default_material());
		return (materials()->nb_materials++);
	}
	else if (o->type == string && ((t_json_string*)o->ptr)->ptr != NULL &&
			(i = -1))
		while (++i < materials()->nb_materials)
			if (materials()->name[i] != NULL &&
				!ft_strcmp(((t_json_string*)o->ptr)->ptr, materials()->name[i]))
				return (i + 1);
	return (0);
}

cl_float4			parse_limit(t_json_value *v, cl_float nc)
{
	t_json_value		**ar;
	cl_float4			out;
	t_json_value_type	*la_norm_le_retour;

	la_norm_le_retour = (t_json_value_type[3])
	{integer | number | null, integer | number | null, integer | number | null};
	if (!ft_json_check_array_types(v, 3, la_norm_le_retour))
		return ((cl_float4){.x = nc, .y = nc, .z = nc, .w = 0.0f});
	ar = ((t_json_array*)v->ptr)->value;
	if (ar[0]->type == null)
		out.x = nc;
	else
		out.x = ar[0]->type == integer ?
		(cl_float)*(int*)ar[0]->ptr : (cl_float)*(double*)ar[0]->ptr;
	if (ar[1]->type == null)
		out.y = nc;
	else
		out.y = ar[1]->type == integer ?
		(cl_float)*(int*)ar[1]->ptr : (cl_float)*(double*)ar[1]->ptr;
	if (ar[2]->type == null)
		out.z = nc;
	else
		out.z = ar[2]->type == integer ?
		(cl_float)*(int*)ar[2]->ptr : (cl_float)*(double*)ar[2]->ptr;
	return ((cl_float4){.x = out.x, .y = out.y, .z = out.z, .w = 0.0f});
}

t_primitive			parse_object_0(t_json_value *o, t_primitive p)
{
	t_json_value	*v[2];

	v[0] = ft_json_search_pair_in_object(o,
		(t_json_string){.length = 8, .ptr = "position"});
	p.position = cl_vector_from_json_array(v[0],
		(cl_float4){.x = 0, .y = 0, .z = 0, .w = 0});
	v[0] = ft_json_search_pair_in_object(o,
		(t_json_string){.length = 9, .ptr = "direction"});
	p.direction = cl_float4_normalize(cl_vector_from_json_array(v[0],
					(cl_float4){.x = 0, .y = 0, .z = 1, .w = 0}));
	v[0] = ft_json_search_pair_in_object(o,
		(t_json_string){.length = 5, .ptr = "limit"});
	v[1] = ft_json_search_pair_in_object(v[0],
		(t_json_string){.length = 8, .ptr = "relative"});
	p.limit.relative = (v[1] != NULL && v[1]->type == boolean &&
						v[1]->ptr != NULL && *(int*)v[1]->ptr);
	v[1] = ft_json_search_pair_in_object(v[0],
		(t_json_string){.length = 4, .ptr = "high"});
	p.limit.high = parse_limit(v[1], FLT_MAX);
	v[1] = ft_json_search_pair_in_object(v[0],
		(t_json_string){.length = 3, .ptr = "low"});
	p.limit.low = parse_limit(v[1], -FLT_MAX);
	return (p);
}

t_primitive			parse_object(t_json_value *o)
{
	t_json_value	*v;
	t_primitive		p;

	if (o == NULL || o->type != object || o->ptr == NULL)
		ft_error(EINTERN, "Parser encountered invalid object\n");
	v = ft_json_search_pair_in_object(o,
		(t_json_string){.length = 4, .ptr = "type"});
	if ((p.type = ft_json_check_string(v, 5,
		(char**)(size_t[5]){(size_t)"sphere", (size_t)"plane",
		(size_t)"cone", (size_t)"cylinder", (size_t)"paraboloid"}, -1)) == -1)
		ft_error(EINTERN, "Parser encountered invalid object\n");
	v = ft_json_search_pair_in_object(o,
		(t_json_string){.length = 8, .ptr = "material"});
	p.material = parse_object_material(v);
	v = ft_json_search_pair_in_object(o,
		(t_json_string){.length = 6, .ptr = "radius"});
	if (v != NULL && (v->type == integer || v->type == number) &&
			v->ptr != NULL)
		p.radius = (v->type == integer) ? (cl_float)*(int*)v->ptr :
										(cl_float)*(double*)v->ptr;
	else
		p.radius = 1.0f;
	return (parse_object_0(o, p));
}

void				parse_objects(t_json_value *o)
{
	t_json_array	*ar;
	unsigned long	i;

	if (o == NULL || o->type != array || (ar = (t_json_array*)o->ptr) == NULL ||
		ar->nb_values == 0 || ar->value == NULL ||
		(*prim() = (t_primitive*)ft_malloc(sizeof(t_primitive) * ar->nb_values))
		== NULL)
		return ;
	argn()->nb_objects = ar->nb_values;
	i = -1;
	while (++i < ar->nb_values)
		(*prim())[i] = parse_object(ar->value[i]);
}
