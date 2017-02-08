/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_json_new_object.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 17:43:24 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/08 23:58:16 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftjson.h>
#include <libft.h>

inline static void	sf_jump_space(const char *src, const unsigned long length,
									unsigned long *pos)
{
	while (ft_isspace(src[*pos]) && *pos < length)
		++*pos;
}

t_json_value		*ft_json_new_object(const char *src,
		const unsigned long length, unsigned long *pos, t_json_value *parent)
{
	t_json_value	*out;
	t_json_object	*obj;
	unsigned long	i;

	if ((out = ft_json_pack_value(parent, object, NULL)) == NULL ||
			*pos >= length || src == NULL || src[*pos] != '{' ||
			(obj = (t_json_object*)ft_malloc(sizeof(t_json_object))) == NULL)
		return (out != NULL ? ft_free(out) : NULL);
	if ((obj->nb_pairs = ft_json_evaluate_object_size(src, length, (*pos)++)) > 0)
	{
		if ((obj->pair = (t_json_pair**)ft_malloc(sizeof(t_json_pair*) *
				obj->nb_pairs)) == NULL && ft_free(out) == NULL)
			return (ft_free(obj));
		i = 0;
		while (i < obj->nb_pairs)
		{
			obj->pair[i++] = ft_json_new_pair(src, length, pos, out);
			sf_jump_space(src, length, pos);
			(src[*pos] == ',' && *pos < length) ? ++*pos : 0;
		}
	}
	else
		obj->pair = NULL;
	sf_jump_space(src, length, pos);
	(src[*pos] == '}' && *pos < length) ? ++*pos : 0;
	out->ptr = (void*)obj;
	return (out);
}
