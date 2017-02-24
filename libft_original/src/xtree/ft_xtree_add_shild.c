/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xtree_add_shild.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/00/00 00:00:00 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/14 14:12:55 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_xtree	*ft_xtree_add_shild(t_xtree *parent, void *data, int type, int security)
{
	t_xtree	*tmp;

	if (parent == NULL || parent->root == NULL || (tmp = ft_xtree_new(data,
		parent->root, type, security)) == NULL || parent->security & XT_RDONLY)
		return (NULL);
	tmp->up = parent;
	if (parent->down != NULL)
	{
		tmp->next = parent->down;
		parent->down->prev = tmp;
	}
	parent->down = tmp;
	return (parent);
}
