/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2l_new_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 09:19:03 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/13 09:19:34 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** create a new orpheline node usable by itself or to be grafted on a list
*/

t_2list	*ft_2l_new_node(void *data)
{
	t_2list	*out;

	out = (t_2list*)ft_malloc(sizeof(t_2list));
	*out = (t_2list){.next = NULL, .prev = NULL, .data = data};
	return (out);
}
