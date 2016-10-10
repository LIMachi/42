/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/02/08 19:50:21 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*tmp;
	t_list	*current;
	t_list	*out;
	t_list	*next;

	if (lst == NULL)
		return (NULL);
	tmp = (*f)(lst);
	current = ft_lstnew(tmp->content, tmp->content_size);
	if (current == NULL)
		return (NULL);
	out = current;
	next = NULL;
	lst = lst->next;
	while (lst != NULL)
	{
		tmp = (*f)(lst);
		next = ft_lstnew(tmp->content, tmp->content_size);
		if (next == NULL)
			return (NULL);
		current->next = next;
		current = next;
		lst = lst->next;
	}
	return (out);
}
