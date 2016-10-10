/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/02/08 19:02:46 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	char	*tmp;
	t_list	*out;

	if (content == NULL)
		content_size = 0;
	if ((out = (t_list *)malloc(sizeof(t_list))) == NULL)
		return (NULL);
	if (content_size)
		if ((tmp = (char *)malloc(sizeof(char) * content_size)) == NULL)
			return (NULL);
	if (content == NULL)
		out->content = NULL;
	else
		out->content = ft_memcpy(tmp, content, content_size);
	out->content_size = content_size;
	out->next = NULL;
	return (out);
}
