/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_json_new_pair.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 17:45:42 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/27 07:55:52 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftjson.h>
#include <libft.h>

t_json_pair		*ft_json_new_pair(const char *src, const unsigned long length,
									unsigned long *pos, t_json_value *parent)
{
	t_json_pair	*out;

	while (ft_isspace(src[*pos]))
		++*pos;
	if ((out = (t_json_pair*)ft_malloc(sizeof(t_json_pair))) == NULL)
		return (out);
	if ((out->key = ft_json_new_string(src, length, pos)) == NULL)
		return (ft_free(out));
	while (ft_isspace(src[*pos]))
		++*pos;
	if (src[*pos] != ':' && ft_free(out->key) == NULL)
		return (ft_free(out));
	++*pos;
	while (ft_isspace(src[*pos]))
		++*pos;
	if ((out->value = ft_json_new_value(src, length, pos, parent)) == NULL &&
			ft_free(out->key) == NULL)
		return (ft_free(out));
	return (out);
}
