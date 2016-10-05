/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alstmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/02/08 18:38:41 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_alist	*ft_alstmap(t_alist *lst, t_alist *(*f)(t_alist *elem))
{
	t_alist *current;
	t_alist *next;
	t_alist *tmp;
	t_alist *out;

	if (lst == NULL)
		return (NULL);
	lst = ft_alsttop(lst);
	tmp = (*f)(lst);
	if (!(current = ft_alstnew(tmp->id, tmp->content, tmp->content_size)))
		return (NULL);
	out = current;
	lst = lst->next;
	while (lst != NULL)
	{
		tmp = (*f)(lst);
		if (!(next = ft_alstnew(tmp->id, tmp->content, tmp->content_size)))
			return (NULL);
		current->next = next;
		next->last = current;
		current = next;
		lst = lst->next;
	}
	return (out);
}
