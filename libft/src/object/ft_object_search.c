/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_object_search.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 20:18:04 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/15 22:56:59 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** search in lst applying function f on each node and returns the first node
** for wich the function return 1, or NULL if none matched
** note: user_data will be sent to the function at each call unmodified
*/

t_object	*ft_object_search(t_object *lst,
				int (*f)(t_object *node, void *user_data), void *user_data)
{
	while (lst != NULL)
	{
		if (f(lst, user_data) == 1)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
