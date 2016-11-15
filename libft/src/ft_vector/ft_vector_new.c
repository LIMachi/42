/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/09 08:29:46 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_vector		*ft_vector_new(const double x, const double y, const double z)
{
	t_vector	*out;

	if ((out = (t_vector*)malloc(sizeof(t_vector))) == NULL)
		return (NULL);
	out->x = x;
	out->y = y;
	out->z = z;
	return (out);
}
