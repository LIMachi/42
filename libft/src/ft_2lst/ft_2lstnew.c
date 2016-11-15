/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2lstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/15 23:37:02 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_2list	*ft_2lstnew(int id, void *content, size_t content_size)
{
	t_2list	*out;
	char	*tmp;

	if (content == NULL)
		content_size = 0;
	if ((out = (t_2list *)ft_memalloc(sizeof(t_2list))) == NULL)
		return (NULL);
	out->id = id;
	if (content_size)
		if ((tmp = (char *)ft_memalloc(sizeof(char) * content_size)) == NULL)
			return (NULL);
	if (content == NULL || content_size == 0)
		out->data = content;
	else
		out->data = ft_memcpy(tmp, content, content_size);
	out->content_size = content_size;
	return (out);
}
