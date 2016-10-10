/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_point_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/15 09:05:19 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/09 08:24:20 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_point	ft_point_add(const t_point a, const t_point b)
{
	return ((t_point){.x = a.x + b.x, .y = a.y + b.y});
}