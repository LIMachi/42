/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_json_new_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 17:40:31 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/08 22:11:31 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftjson.h>
#include <libft.h>
#include <stdio.h>

inline static t_json_value	*sf_json_new_value(t_json_value *parent,
				const char *src, const unsigned long length, unsigned long *pos)
{
	t_json_string	*str;

	if ((str = ft_json_new_string(src, length, pos)) == NULL)
		return (NULL);
	return (ft_json_pack_value(parent, string, str));
}

t_json_value				*ft_json_new_value(const char *src,
		const unsigned long length, unsigned long *pos, t_json_value *parent)
{
	void				*tmp;
	t_json_value_type	type;

	while (ft_isspace(src[*pos]))
		++(*pos);
	if ((type = ft_json_evaluate_value_type(src, length, *pos)) == boolean)
	{
		if ((tmp = ft_malloc(sizeof(int))) == NULL)
			return (NULL);
		ft_void((*(int*)tmp = (src[(*pos)++] == 't' && *pos + 2 < length &&
		src[(*pos)++] == 'r' && src[(*pos)++] == 'u' && src[(*pos)++] == 'e'))
		|| ((*pos) += 4));
		return (ft_json_pack_value(parent, boolean, tmp));
	}
	if (type == null && ((*pos) += 4))
		return (ft_json_pack_value(parent, null, NULL));
	if (type == number || type == integer)
		return (ft_json_new_number(src, length, pos, parent));
	if (type == string)
		return (sf_json_new_value(parent, src, length, pos));
	if (type == array)
		return (ft_json_new_array(src, length, pos, parent));
	if (type == object)
		return (ft_json_new_object(src, length, pos, parent));
	return (NULL);
}
