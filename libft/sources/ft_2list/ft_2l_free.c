/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2l_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 09:20:34 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/13 09:20:47 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** wanring: do not touch data in nodes, you must free allocated data manually
** or use recursivelly ft_free(ft_2l_free_node(node))
*/

void	*ft_2l_free(t_2list **head)
{
	t_2list	*tmp;

	tmp = *head;
	while (tmp != NULL)
		if (tmp->next != NULL)
		{
			tmp = tmp->next;
			ft_free(tmp->prev);
		}
		else
		{
			ft_free(tmp);
			tmp = NULL;
		}
	return (NULL);
}
