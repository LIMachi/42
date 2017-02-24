/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/18 13:59:45 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	char	*tmp;
	t_list	*out;

	tmp = NULL;
	if (content == NULL)
		content_size = 0;
	if ((out = (t_list *)ft_malloc(sizeof(t_list))) == NULL)
		return (NULL);
	if (content_size)
		if ((tmp = (char *)ft_malloc(sizeof(char) * content_size)) == NULL)
			return (NULL);
	if (content == NULL && content_size > 0)
		out->data = NULL;
	else
		out->data = ft_memcpy(tmp, content, content_size);
	out->content_size = content_size;
	out->next = NULL;
	*(uint32_t*)&out->object_type = OBJECT_LIST;
	*(uint64_t*)&out->object_functions = OBJECT_FUNCTIONS_LIST;
	return (out);
}
