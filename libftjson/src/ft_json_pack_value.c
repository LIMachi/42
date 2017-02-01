/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_json_pack_value.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 17:47:23 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/27 07:56:02 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftjson.h>
#include <libft.h>

t_json_value	*ft_json_pack_value(t_json_value *parent,
									t_json_value_type type, void *ptr)
{
	t_json_value	*out;

	if ((out = (t_json_value*)ft_malloc(sizeof(t_json_value))) == NULL)
		return (NULL);
	out->type = type;
	out->ptr = ptr;
	out->parent = parent;
	return (out);
}
