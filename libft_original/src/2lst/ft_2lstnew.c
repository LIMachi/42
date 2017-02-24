/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2lstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/17 14:28:10 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_2list	*ft_2lstnew(const uint64_t *id, void *content, size_t content_size)
{
	t_2list	*out;
	char	*tmp;

	if (content == NULL)
		content_size = 0;
	if ((out = (t_2list *)ft_memalloc(sizeof(t_2list))) == NULL)
		return (NULL);
	if (id != NULL)
		out->id = *id;
	else
		out->id = 0;
	if (content_size)
		if ((tmp = (char *)ft_memalloc(sizeof(char) * content_size)) == NULL)
			return (NULL);
	if (content == NULL || content_size == 0)
		out->data = content;
	else
		out->data = ft_memcpy(tmp, content, content_size);
	out->content_size = content_size;
	*(uint32_t*)&out->object_type = OBJECT_DLLIST;
	*(uint64_t*)&out->object_functions = OBJECT_FUNCTION_DLLIST;
	return (out);
}
