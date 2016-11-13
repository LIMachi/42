/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2l_free_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 09:21:01 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/13 09:21:13 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** link prev and next node together, free node and return data
*/

void	*ft_2l_free_node(t_2list *node)
{
	void	*tmp;

	if (node->next != NULL)
		node->next->prev = node->prev;
	if (node->prev != NULL)
		node->prev->next = node->next;
	tmp = node->data;
	ft_free(node);
	return (tmp);
}
