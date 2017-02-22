/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alstdeltop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/02/08 18:38:03 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_alist	*ft_alstdeltop(t_alist *lst, void (*del)(void *, size_t))
{
	if (lst != NULL)
		lst = ft_alsttop(lst);
	else
		return (NULL);
	if (lst->next != NULL)
	{
		lst = lst->next;
		ft_alstdelone(lst->last, del);
		lst->last = NULL;
		return (lst);
	}
	else
	{
		ft_alstdelone(lst, del);
		return (NULL);
	}
}
