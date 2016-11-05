/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_point_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 04:30:30 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/14 14:10:31 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_point	*ft_point_init(t_point *p, const int x, const int y)
{
	if (p != NULL)
		*p = (t_point){.x = x, .y = y};
	return (p);
}
