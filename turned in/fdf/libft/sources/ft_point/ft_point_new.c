/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_point_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 04:27:59 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/14 14:10:34 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_point	*ft_point_new(const int x, const int y)
{
	t_point *out;

	if ((out = (t_point*)malloc(sizeof(t_point))) == NULL)
		return (NULL);
	out->x = x;
	out->y = y;
	return (out);
}
