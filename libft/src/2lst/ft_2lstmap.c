/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2lstmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/17 08:55:33 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_2list	*ft_2lstmap(t_2list *lst, t_2list *(*f)(t_2list *elem))
{
	t_2list *current;
	t_2list *next;
	t_2list *tmp;
	t_2list *out;

	if (lst == NULL)
		return (NULL);
	lst = ft_2lsttop(lst);
	tmp = (*f)(lst);
	if (!(current = ft_2lstnew(&tmp->id, tmp->data, tmp->content_size)))
		return (NULL);
	out = current;
	lst = lst->next;
	while (lst != NULL)
	{
		tmp = (*f)(lst);
		if (!(next = ft_2lstnew(&tmp->id, tmp->data, tmp->content_size)))
			return (NULL);
		current->next = next;
		next->prev = current;
		current = next;
		lst = lst->next;
	}
	return (out);
}
