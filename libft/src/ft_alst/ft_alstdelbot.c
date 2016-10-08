/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alstdelbot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/02/08 18:36:52 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_alist	*ft_alstdelbot(t_alist *lst, void (*del)(void *, size_t))
{
	if (lst != NULL)
		lst = ft_alstbot(lst);
	else
		return (NULL);
	if (lst->last != NULL)
	{
		lst = lst->last;
		ft_alstdelone(lst->next, del);
		lst->next = NULL;
		return (lst);
	}
	else
	{
		ft_alstdelone(lst, del);
		return (NULL);
	}
}
