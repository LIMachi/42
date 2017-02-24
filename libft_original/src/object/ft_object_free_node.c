/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_object_free_node.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 22:07:35 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/15 22:56:49 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_object_free_node(t_object *node)
{
	void	*tmp;

	if (node->type == OBJECT_DLLIST || node->type == OBJECT_XTREE)
	{
		if (node->next != NULL && (node->next->type == OBJECT_DLLIST ||
								node->next->type == OBJECT_XTREE))
			((t_2list*)node->next)->prev = ((t_2list*)node)->prev;
		if (((t_2list*)node)->prev != NULL)
			((t_object*)((t_2list*)node)->prev)->next = node->next;
	}
	tmp = node->data;
	ft_free(node);
	return (tmp);
}
