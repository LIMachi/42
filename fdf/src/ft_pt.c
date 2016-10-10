/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/15 08:51:12 by hmartzol          #+#    #+#             */
/*   Updated: 2016/07/15 09:00:30 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_point	ft_ptadd(t_point a, t_point b)
{
	return ((t_point){a.x + b.x, a.y + b.y});
}

t_point	ft_ptsub(t_point a, t_point b)
{
	return ((t_point){a.x - b.x, a.y - b.y});
}

void	ft_ptswap(t_point *a, t_point *b)
{
	t_point t;

	t = *a;
	*a = *b;
	*b = t;
}
