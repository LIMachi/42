/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 17:23:42 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/22 17:31:29 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_env_clear(void)
{
	t_object	*node;
	t_object	*tmp;

	if ((node = *ft_global_env()) == NULL)
		return ;
	while (node != NULL)
	{
		tmp = node->next;
		(void)ft_object_free_node(node);
		node = tmp;
	}
}
