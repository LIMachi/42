/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alstsearchid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/02/08 18:43:26 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_alist	*ft_alstsearchid(int id, t_alist *lst)
{
	t_alist	*top;
	t_alist	*bot;

	if (lst == NULL || lst->id == id)
		return (lst);
	top = lst;
	bot = lst;
	while (top->id != id && bot->id != id && (top->last || bot->next))
	{
		top = top->last;
		bot = bot->next;
	}
	if (top && top->id == id)
		return (top);
	if (bot && bot->id == id)
		return (bot);
	return (NULL);
}
