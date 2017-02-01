/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_json_new_string.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 17:55:33 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/27 07:55:56 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftjson.h>
#include <libft.h>

t_json_string	*ft_json_new_string(const char *src, const unsigned long length,
									unsigned long *pos)
{
	t_json_string	*out;
	unsigned long	len;

	if (src == NULL || src[(*pos)++] != '\"' || *pos >= length)
		return (NULL);
	len = *pos;
	while (len < length && src[len] != '\0' && (src[len] != '\"'))
		++len;
	if (len == length || src[len] == '\0')
		return (NULL);
	if ((out = (t_json_string*)ft_malloc(sizeof(t_json_string))) == NULL)
		return (NULL);
	out->length = len - *pos;
	if ((out->ptr = ft_strndup(&src[*pos], out->length)) == NULL)
		return (ft_free(out));
	*pos += out->length + 1;
	return (out);
}
