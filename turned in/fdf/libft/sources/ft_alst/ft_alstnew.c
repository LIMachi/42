/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/10 13:52:48 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_alist	*ft_alstnew(int id, void *content, size_t content_size)
{
	t_alist	*out;
	char	*tmp;

	if (content == NULL)
		content_size = 0;
	if ((out = (t_alist *)malloc(sizeof(t_alist))) == NULL)
		return (NULL);
	out->id = id;
	if (content_size)
		if ((tmp = (char *)malloc(sizeof(char) * content_size)) == NULL)
			return (NULL);
	if (content == NULL)
		out->data = NULL;
	else
		out->data = ft_memcpy(tmp, content, content_size);
	out->content_size = content_size;
	out->prev = NULL;
	out->next = NULL;
	return (out);
}
