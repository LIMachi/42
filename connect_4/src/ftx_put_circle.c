/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_put_circle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 14:16:25 by hmartzol          #+#    #+#             */
/*   Updated: 2017/03/02 12:52:31 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <connect_4.h>

static void	sf_putoctant(t_mlx mlx, t_pixel center, t_point pos)
{
	ftx_put_pixel_img(mlx, center.pos.x + pos.x, center.pos.y + pos.y,
						center.color);
	ftx_put_pixel_img(mlx, center.pos.x + pos.y, center.pos.y + pos.x,
						center.color);
	ftx_put_pixel_img(mlx, center.pos.x - pos.x, center.pos.y + pos.y,
						center.color);
	ftx_put_pixel_img(mlx, center.pos.x - pos.y, center.pos.y + pos.x,
						center.color);
	ftx_put_pixel_img(mlx, center.pos.x + pos.x, center.pos.y - pos.y,
						center.color);
	ftx_put_pixel_img(mlx, center.pos.x + pos.y, center.pos.y - pos.x,
						center.color);
	ftx_put_pixel_img(mlx, center.pos.x - pos.x, center.pos.y - pos.y,
						center.color);
	ftx_put_pixel_img(mlx, center.pos.x - pos.y, center.pos.y - pos.x,
						center.color);
}

/*
** Andres algorithm
*/

static void	sf_putcirclea(t_mlx mlx, t_pixel center, int radius)
{
	t_point	pos;
	int		d;

	pos = ft_point(0, radius);
	d = radius - 1;
	while (pos.y >= pos.x)
	{
		sf_putoctant(mlx, center, pos);
		if (d >= 2 * pos.x)
			d -= 2 * ++pos.x;
		else if (d < 2 * (radius - pos.y))
			d += 2 * --pos.y;
		else
			d += 2 * (--pos.y - pos.x++);
	}
}

static void	sf_putcirclef(t_mlx mlx, t_pixel center, int radius)
{
	t_point	pos;

	pos.y = -radius - 1;
	while (++pos.y <= radius && (pos.x = -radius - 1))
		while (++pos.x <= radius)
			if (pos.x * pos.x + pos.y * pos.y <= radius * radius)
				ftx_put_pixel_img(mlx, pos.x + center.pos.x,
									pos.y + center.pos.y, center.color);
}

/*
** Midpoint algorithm (Bresenham)
*/

void		ftx_put_circle(t_mlx mlx, t_pixel center, int radius, int mode)
{
	t_point	pos;
	int		d;

	if (mode & MODE_FILL)
		sf_putcirclef(mlx, center, radius);
	if (mode & MODE_ANDRES)
		sf_putcirclea(mlx, center, radius);
	if ((mode & MODE_ANDRES) | (mode & MODE_FILL))
		return ;
	pos = ft_point(radius, 0);
	d = 1 - center.pos.x;
	while (pos.y <= pos.x)
	{
		sf_putoctant(mlx, center, pos);
		++pos.y;
		if (d <= 0)
			d += 2 * pos.y + 1;
		else
			d += 2 * (pos.y - --pos.x) + 1;
	}
}
