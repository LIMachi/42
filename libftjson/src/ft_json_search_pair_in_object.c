/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_json_search_pair_in_object.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 19:27:56 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/27 07:56:11 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftjson.h>
#include <libft.h>

t_json_value	*ft_json_search_pair_in_object(const t_json_value *value,
												const t_json_string key)
{
	unsigned long	i;
	t_json_object	*obj;

	if (value == NULL || value->type != object)
		return (NULL);
	obj = (t_json_object*)value->ptr;
	i = 0;
	while (i < obj->nb_pairs)
	{
		if (obj->pair[i] != NULL && obj->pair[i]->key != NULL &&
			obj->pair[i]->value != NULL && obj->pair[i]->value->ptr != NULL &&
			obj->pair[i]->key->length == key.length &&
			obj->pair[i]->key->ptr != NULL &&
			ft_strcmp(obj->pair[i]->key->ptr, key.ptr) == 0)
			break ;
		++i;
	}
	if (i != obj->nb_pairs)
		return (obj->pair[i]->value);
	return (NULL);
}
