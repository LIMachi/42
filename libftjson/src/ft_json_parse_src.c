/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_json_parse_src.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 17:48:44 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/27 07:56:05 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftjson.h>
#include <libft.h>

t_json_value	*ft_json_parse_src(const char *src)
{
	unsigned long		pos;
	t_json_value		*root;

	pos = 0;
	if (src == NULL)
		return (NULL);
	if ((root = ft_json_new_value(src, ft_strlen(src), &pos, NULL)) == NULL)
		return (NULL);
	root->parent = (void*)root;
	return (root);
}
