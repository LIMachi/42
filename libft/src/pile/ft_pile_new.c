/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pile_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 13:20:01 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/18 12:41:24 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_pile	*ft_pile_new(unsigned int size)
{
	t_pile	*out;

	if (size == 0)
		return (NULL);
	if ((out = (t_pile*)ft_memalloc(sizeof(t_pile))) == NULL)
		return (NULL);
	if ((out->data = (void**)ft_memalloc(sizeof(void*) * size)) == NULL)
		return (NULL);
	out->size = size;
	out->head = 0;
	return (out);
}
