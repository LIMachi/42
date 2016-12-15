/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_selection_square.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 14:30:31 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/29 07:49:50 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <libftx.h>

static inline t_point	sf_correct_coord(t_image *img, t_point p)
{
	if (p.x >= img->size.x)
		p.x = img->size.x - 1;
	if (p.y >= img->size.y)
		p.y = img->size.y - 1;
	if (p.x < 0)
		p.x = 0;
	if (p.y < 0)
		p.y = 0;
	return (p);
}

t_image					*ftx_put_selection_square(t_image *img, const t_point a,
									const t_point b, const int color)
{
	t_point	start;
	t_point	end;
	t_point	pos;

	start = ft_point(a.x < b.x ? a.x : b.x, a.y < b.y ? a.y : b.y);
	end = ft_point(a.x > b.x ? a.x : b.x, a.y > b.y ? a.y : b.y);
	start = sf_correct_coord(img, start);
	end = sf_correct_coord(img, end);
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
