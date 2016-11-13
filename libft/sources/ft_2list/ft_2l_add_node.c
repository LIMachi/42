/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2l_add_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 09:20:03 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/13 09:20:19 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** graft a node to the head of a list (the new node will be set as the new head)
*/

t_2list	**ft_2l_add_node(t_2list **head, t_2list *node)
{
	if (*head != NULL)
	{
		(*head)->prev = node;
		node->next = *head;
	}
	*head = node;
	return (head);
}
