/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_json_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 19:39:26 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/27 07:56:15 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftjson.h>
#include <libft.h>

t_json_string	*ft_json_string(const char *str)
{
	t_json_string	*out;

	if (str == NULL)
		return (NULL);
	if ((out = (t_json_string*)ft_malloc(sizeof(t_json_string))) == NULL)
		return (NULL);
	if ((out->ptr = ft_strdup(str)) == NULL)
		return (ft_free(out));
	out->length = ft_strlen(str);
	return (out);
}
