/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttostr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/20 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/10 13:55:54 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_lsttostr(t_list *lst)
{
	t_list	*tmp;
	size_t	size;
	char	*out;

	tmp = lst;
	size = 1;
	while (tmp)
	{
		size += tmp->content_size - 1;
		tmp = tmp->next;
	}
	if ((out = (char *)ft_memalloc(sizeof(char) * size)) == NULL)
		return (NULL);
	tmp = lst;
	while (tmp)
	{
		ft_strcat(out, tmp->data);
		tmp = tmp->next;
	}
	return (out);
}
