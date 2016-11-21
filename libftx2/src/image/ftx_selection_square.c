/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_selection_square.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 14:30:31 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/21 17:11:07 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <libftx.h>

t_image	*ftx_put_selection_square(t_image *img, const t_point a,
									const t_point b, const int color)
{
	t_point	start;
	t_point	end;
	t_point	pos;

	start = ft_point(a.x < b.x ? a.x : b.x, a.y < b.y ? a.y : b.y);
	end = ft_point(a.x > b.x ? a.x : b.x, a.y > b.y ? a.y : b.y);
	pos.y = start.y - 1;
	while (++pos.y < end.y)
	{
		pos.x = start.x - 1;
		while (++pos.x < end.x)
			ftx_slerp_pixel(img, pos, color, 1.0 - 0.7 * (pos.x != start.x &&
				pos.x != end.x - 1 && pos.y != start.y && pos.y != end.y - 1));
	}
	return (img);
}
