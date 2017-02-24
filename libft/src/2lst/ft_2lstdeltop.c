/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2lstdeltop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/15 22:49:56 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_2list	*ft_2lstdeltop(t_2list *lst, void (*del)(void *, size_t))
{
	if (lst != NULL)
		lst = ft_2lsttop(lst);
	else
		return (NULL);
	if (lst->next != NULL)
	{
		lst = lst->next;
		ft_2lstdelone(lst->prev, del);
		lst->prev = NULL;
		return (lst);
	}
	else
	{
		ft_2lstdelone(lst, del);
		return (NULL);
	}
}
