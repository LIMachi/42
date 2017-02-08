/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_materials.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 02:01:09 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/30 03:01:28 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_material			parse_material_0(t_json_value *m, t_material out)
{
	t_json_value	*v;

	v = ft_json_search_pair_in_object(m,
		(t_json_string){.length = 5, .ptr = "color"});
	out.color = cl_vector_from_json_array(v, out.color);
	v = ft_json_search_pair_in_object(m,
		(t_json_string){.length = 7, .ptr = "diffuse"});
	(v != NULL && v->type == number && v->ptr != NULL) ?
		out.diffuse = (cl_float) * (double*)v->ptr : 0;
	v = ft_json_search_pair_in_object(m,
		(t_json_string){.length = 8, .ptr = "specular"});
	(v != NULL && v->type == number && v->ptr != NULL) ?
		out.specular = (cl_float) * (double*)v->ptr : 0;
	v = ft_json_search_pair_in_object(m,
		(t_json_string){.length = 10, .ptr = "reflection"});
	(v != NULL && v->type == number && v->ptr != NULL) ?
		out.reflection = (cl_float) * (double*)v->ptr : 0;
	v = ft_json_search_pair_in_object(m,
		(t_json_string){.length = 7, .ptr = "texture"});
	out.texture = parse_texture(v, out.texture);
	return (out);
}

t_material			parse_material(t_json_value *m, t_material out)
{
	t_json_value	*v[2];

	if (m == NULL || m->type != object || m->ptr == NULL)
		return (out);
	v[0] = ft_json_search_pair_in_object(m,
		(t_json_string){.length = 12, .ptr = "perturbation"});
	v[1] = ft_json_search_pair_in_object(v[0],
		(t_json_string){.length = 6, .ptr = "normal"});
	(v[1] != NULL && v[1]->type == number && v[1]->ptr != NULL) ?
		out.perturbation.normal = (cl_float) * (double*)v[1]->ptr : 0;
	v[1] = ft_json_search_pair_in_object(v[0],
		(t_json_string){.length = 5, .ptr = "color"});
	out.perturbation.color = ft_json_check_string(v[1], 3,
	(char**)(size_t[3]){(size_t)NULL, (size_t)"sine", (size_t)"checkerboard"},
	out.perturbation.color);
	return (parse_material_0(m, out));
}

char				*new_material(t_json_pair *p, unsigned long i)
{
	char	*out;

	if (p == NULL || p->key == NULL || p->value == NULL || p->key->ptr == NULL
		|| p->key->length == 0 || (out = ft_strdup(p->key->ptr)) == NULL)
		return (NULL);
	materials()->materials[ft_strcmp("default", out) ? i + 1 : 0] =
		parse_material(p->value, default_material());
	return (out);
}

void				*parse_materials(t_json_value *m)
{
	t_json_object	*obj;
	t_pair			*out;
	unsigned long	i;

	out = NULL;
	if (m == NULL || m->type != object || m->ptr == NULL ||
		(obj = (t_json_object*)m->ptr)->nb_pairs == 0 || obj->pair == NULL ||
		(out = (t_pair*)ft_malloc(sizeof(t_pair) * obj->nb_pairs)) == NULL ||
		(materials()->materials =
		ft_malloc(sizeof(t_material) * (obj->nb_pairs + 1))) == NULL)
		return (out != NULL ? ft_free(out) : NULL);
	if ((materials()->name =
			ft_malloc(sizeof(char*) * (obj->nb_pairs + 1))) == NULL)
	{
		ft_memdel((void**)&materials()->materials);
		return (ft_free(out));
	}
	i = -1;
	materials()->materials[0] = default_material();
	while (++i < obj->nb_pairs)
		materials()->name[i] = new_material(obj->pair[i], i);
	materials()->nb_materials = obj->nb_pairs + 1;
	return (NULL);
}
