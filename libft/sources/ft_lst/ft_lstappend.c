/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 18:52:52 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/10 13:54:27 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstappend(t_list **alst, t_list *new)
{
	t_list	*current;

	if (alst == NULL)
		return ;
	current = *alst;
	if (current != NULL)
	{
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
	else
		*alst = new;
}
