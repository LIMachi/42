/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_json_new_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 17:42:33 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/08 23:33:43 by hmartzol         ###   ########.fr       */
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

t_json_value		*ft_json_new_array(const char *src,
		const unsigned long length, unsigned long *pos, t_json_value *parent)
{
	t_json_value	*out;
	t_json_array	*ar;
	unsigned long	i;

	if ((out = ft_json_pack_value(parent, array, NULL)) == NULL ||
			*pos >= length || src == NULL || src[*pos] != '[' ||
			(ar = (t_json_array*)ft_malloc(sizeof(t_json_array))) == NULL)
		return (out != NULL ? ft_free(out) : NULL);
	if ((ar->nb_values = ft_json_evaluate_array_size(src, length, (*pos)++)) > 0)
	{
		if ((ar->value = (t_json_value**)ft_malloc(sizeof(t_json_value*) *
				ar->nb_values)) == NULL && ft_free(out))
			return (ft_free(ar));
		i = 0;
		while (i < ar->nb_values)
		{
			ar->value[i++] = ft_json_new_value(src, length, pos, out);
			sf_jump_space(src, length, pos);
			(src[*pos] == ',' && *pos < length) ? ++*pos : 0;
		}
	}
	else
		ar->value = NULL;
	sf_jump_space(src, length, pos);
	(src[*pos] == ']' && *pos < length) ? ++*pos : 0;
	out->ptr = (void*)ar;
	return (out);
}
