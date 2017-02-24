/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_object_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 19:54:26 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/15 19:59:48 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_object	*ft_object_new(void *data)
{
	t_object	*out;

	out = (t_object*)ft_malloc(sizeof(t_object));
	*(uint32_t*)&out->type = OBJECT;
	*(uint64_t*)&out->functions = OBJECT_FUNCTION;
	out->data = data;
	out->next = NULL;
	return (out);
}
