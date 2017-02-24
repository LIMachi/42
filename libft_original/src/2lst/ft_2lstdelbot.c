/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2lstdelbot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/15 22:50:27 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_2list	*ft_2lstdelbot(t_2list *lst, void (*del)(void *, size_t))
{
	if (lst != NULL)
		lst = ft_2lstbot(lst);
	else
		return (NULL);
	if (lst->prev != NULL)
	{
		lst = lst->prev;
		ft_2lstdelone(lst->next, del);
		lst->next = NULL;
		return (lst);
	}
	else
	{
		ft_2lstdelone(lst, del);
		return (NULL);
	}
}
