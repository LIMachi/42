/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2lsearchcontent.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 16:28:18 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/05 16:47:54 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** note: it searches the corresponding content pointer, not the data pointed by
** the content pointer
*/

t_2list	ft_2lsearchcontent(t_2list *lst, void *content)
{
	t_2list	*top;
	t_2list	*bot;

	if (lst == NULL || lst->data == content)
		return (lst);
	top = lst;
	bot = lst;
	while (top->data != content && bot->data !=  content &&
				(top->prev != NULL || bot->next != NULL))
	{
		if (top != NULL)
			top = top->prev;
		if (bot != NULL)
			bot = bot->next;
	}
	if (top && top->data == content)
		return (top);
	if (bot && bot->data == content)
		return (bot);
	return (NULL);
}
