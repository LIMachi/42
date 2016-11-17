/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2lstdelnode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/17 09:10:23 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_2list	*ft_2lstdelnode(t_2list *lst, void (*del)(void *, size_t))
{
	t_2list	*out;

	if (lst->next == NULL)
		return (ft_2lstdelbot(lst, del));
	if (lst->prev == NULL)
		return (ft_2lstdeltop(lst, del));
	lst->prev->next = lst->next;
	lst->next->prev = lst->prev;
	out = lst->prev;
	ft_2lstdelone(lst, del);
	return (out);
}
