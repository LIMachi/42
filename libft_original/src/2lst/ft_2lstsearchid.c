/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2lstsearchid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/17 08:50:59 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_2list	*ft_2lstsearchid(const uint64_t *id, t_2list *lst)
{
	t_2list	*top;
	t_2list	*bot;

	if (lst == NULL || lst->id == *id)
		return (lst);
	top = lst;
	bot = lst;
	while (top->id != *id && bot->id != *id && (top->prev || bot->next))
	{
		top = top->prev;
		bot = bot->next;
	}
	if (top && top->id == *id)
		return (top);
	if (bot && bot->id == *id)
		return (bot);
	return (NULL);
}
