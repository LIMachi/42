/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pile_new_filo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 13:20:01 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/14 13:20:20 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_pile_filo	*ft_pile_new_filo(unsigned int size)
{
	t_pile_filo	*out;

	if (size == 0)
		return (NULL);
	if ((out = (t_pile_filo*)ft_memalloc(sizeof(t_pile_filo))) == NULL)
		return (NULL);
	if ((out->data = (void**)ft_memalloc(sizeof(void*) * size)) == NULL)
		return (NULL);
	out->size = size;
	out->head = 0;
	return (out);
}
