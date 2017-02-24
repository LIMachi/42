/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_object_add.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 20:00:12 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/15 22:56:30 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_object	**ft_object_add(t_object **list, t_object *node)
{
	if (list == NULL)
	{
		ft_error(EINVAL, "ft_object_add got NULL as **list\n");
		return (NULL);
	}
	if (node == NULL)
		return (list);
	if (*list != NULL)
	{
		if ((*list)->type == OBJECT_DLLIST || (*list)->type == OBJECT_XTREE)
			((t_2list*)(*list))->prev = (t_2list*)node;
		node->next = *list;
	}
	*list = node;
	return (list);
}
