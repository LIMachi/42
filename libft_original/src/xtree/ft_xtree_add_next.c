/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xtree_add_next.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/00/00 00:00:00 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/14 14:12:53 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_xtree	*ft_xtree_add_next(t_xtree *parent, void *data, int type, int security)
{
	t_xtree	*tmp;

	if (parent == NULL || parent->root == NULL || (tmp = ft_xtree_new(data,
		parent->root, type, security)) == NULL || parent->security & XT_RDONLY)
		return (NULL);
	tmp->prev = parent;
	if (parent->next != NULL)
	{
		tmp->next = parent->next;
		parent->next->prev = tmp;
	}
	parent->next = tmp;
	return (parent);
}
