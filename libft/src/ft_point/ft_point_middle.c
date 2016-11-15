/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_point_middle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/17 18:10:03 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/01 16:04:53 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_point	ft_point_middle(const t_point a, const t_point b)
{
	return ((t_point){(b.x + a.x) / 2, (b.y + a.y) / 2});
}
