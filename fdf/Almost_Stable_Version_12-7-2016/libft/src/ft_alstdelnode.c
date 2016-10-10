/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alstdelnode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/06/15 06:34:35 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_alist	*ft_alstdelnode(t_alist *lst, void (*del)(void *, size_t))
{
	t_alist	*out;

	if (lst->next == NULL)
		return (ft_alstdelbot(lst, del));
	if (lst->last == NULL)
		return (ft_alstdeltop(lst, del));
	lst->last->next = lst->next;
	lst->next->last = lst->last;
	out = lst->last;
	ft_alstdelone(lst, del);
	return (out);
}
