/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_images.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 17:10:35 by hmartzol          #+#    #+#             */
/*   Updated: 2017/03/08 04:14:58 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <stdio.h>

int					add_texture(void)
{
	t_ubmp			*ubmp;

	if ((ubmp = ft_bmp_to_ubmp(ft_bitmap_file_load(
		textures_holder()->path[textures_holder()->nb_info]))) == NULL)
		return (ft_error(EINTERN, "bitmap could not be found/opened\n"));
	textures_holder()->info[textures_holder()->nb_info].size =
		(cl_int2){.x = ubmp->size.x, .y = ubmp->size.y};
	if (textures_holder()->nb_info)
		textures_holder()->info[textures_holder()->nb_info].index =
		textures_holder()->info[textures_holder()->nb_info - 1].index +
		textures_holder()->info[textures_holder()->nb_info - 1].size.x *
		textures_holder()->info[textures_holder()->nb_info - 1].size.y;
	else
		textures_holder()->info[textures_holder()->nb_info].index = 0;
	textures_holder()->total_raw_size =
		textures_holder()->info[textures_holder()->nb_info].index +
		ubmp->size.x * ubmp->size.y;
	textures_holder()->raw_bmp = ft_reallocf(textures_holder()->raw_bmp,
		textures_holder()->info[textures_holder()->nb_info].index * sizeof(int),
		textures_holder()->total_raw_size * sizeof(int));
	ft_memmove(&textures_holder()->raw_bmp[textures_holder()->info[
		textures_holder()->nb_info].index], ubmp->data,
		ubmp->size.x * ubmp->size.y * sizeof(int));
	ft_free(ubmp->data);
	return ((int)(size_t)ft_free(ubmp));
}

void				parse_image(t_json_value *sp)
{
	t_json_string	*str;
	char			buff[PATH_MAX];
	int				i;

	if (sp == NULL || sp->type != string || sp->ptr == NULL)
		return ;
	str = (t_json_string*)sp->ptr;
	ft_realpath(str->ptr, buff);
	i = -1;
	while (++i < textures_holder()->nb_info)
		if (!ft_strcmp(buff, textures_holder()->path[i]))
			break ;
	if (i == textures_holder()->nb_info)
	{
		textures_holder()->path = ft_reallocf(textures_holder()->path,
			sizeof(char**) * textures_holder()->nb_info,
			sizeof(char**) * (textures_holder()->nb_info + 1));
		textures_holder()->info = ft_reallocf(textures_holder()->info,
			sizeof(t_img_info) * textures_holder()->nb_info,
			sizeof(t_img_info) * (textures_holder()->nb_info + 1));
		textures_holder()->path[textures_holder()->nb_info] = ft_strdup(buff);
		(void)add_texture();
		++textures_holder()->nb_info;
	}
}

void				parse_skybox(t_json_value *m)
{
	t_json_value	*v;

	if (m == NULL || m->type != object || m->ptr == NULL)
		return ;
	v = ft_json_search_pair_in_object(m,
		(t_json_string){.length = 6, .ptr = "skybox"});
	parse_image(ft_json_search_pair_in_object(v,
		(t_json_string){.length = 4, .ptr = "file"}));
}

void				parse_material_images(t_json_value *m)
{
	t_json_value	*v;

	if (m == NULL || m->type != object || m->ptr == NULL)
		return ;
	v = ft_json_search_pair_in_object(m,
		(t_json_string){.length = 7, .ptr = "texture"});
	parse_image(ft_json_search_pair_in_object(v,
		(t_json_string){.length = 4, .ptr = "file"}));
}

/*
** first, search and resolve all texture paths, then load all texture in a
** 1dimension cl_int array while making info and make pairs betwen path and info
** pairs will then be used when loading materials and objects
*/

void				parse_images(t_json_value *root)
{
	t_json_value	*v;
	t_json_object	*obj;
	t_json_array	*ar;
	unsigned long	i;

	v = ft_json_search_pair_in_object(root,
		(t_json_string){.length = 9, .ptr = "materials"});
	if (v != NULL && v->type == object &&
			(obj = (t_json_object*)v->ptr) != NULL && obj->nb_pairs != 0 &&
			obj->pair != NULL && (i = -1))
		while (++i < obj->nb_pairs)
			if (obj->pair[i] != NULL)
				parse_material_images(obj->pair[i]->value);
	v = ft_json_search_pair_in_object(root,
		(t_json_string){.length = 7, .ptr = "objects"});
	if (v != NULL && v->type == array &&
		(ar = (t_json_array*)v->ptr) != NULL && ar->nb_values != 0 &&
		ar->value != NULL && (i = -1))
		while (++i < ar->nb_values)
			parse_material_images(ft_json_search_pair_in_object(ar->value[i],
				(t_json_string){.length = 8, .ptr = "material"}));
	v = ft_json_search_pair_in_object(root,
		(t_json_string){.length = 14, .ptr = "render_options"});
	parse_skybox(v);
}
