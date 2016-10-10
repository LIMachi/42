/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alstappend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 18:52:52 by hmartzol          #+#    #+#             */
/*   Updated: 2016/02/08 18:32:08 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_alstappend(t_alist *lst, t_alist *new)
{
	if (lst != NULL)
		lst = ft_alstbot(lst);
	else
		return ;
	lst->next = new;
	new->last = lst;
}
