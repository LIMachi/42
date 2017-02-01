/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_point_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 04:27:59 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/18 23:52:04 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_point	*ft_point_new(const int x, const int y)
{
	t_point *out;

	if ((out = (t_point*)ft_malloc(sizeof(t_point))) == NULL)
		return (NULL);
	out->x = x;
	out->y = y;
	return (out);
}
