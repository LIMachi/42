/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/15 00:22:19 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/21 17:10:32 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <libftx.h>

inline static void	sf_line1(t_image *img, t_ftx_line_data v, t_point color)
{
	v.cr[1] = (((color.y >> 16) & 0xFF) - v.cr[0]) / (v.d.y >> 1);
	v.cg[1] = (((color.y >> 8) & 0xFF) - v.cg[0]) / (v.d.y >> 1);
	v.cb[1] = ((color.y & 0xFF) - v.cb[0]) / (v.d.y >> 1);
	v.v = v.d.x - (v.d.y >> 1);
	while (v.a.y != v.b.y)
	{
		if (v.v >= 0)
		{
			v.a.x += v.s.x;
			v.v -= v.d.y;
		}
		v.a.y += v.s.y;
		v.v += v.d.x;
		v.cr[0] += v.cr[1];
		v.cg[0] += v.cg[1];
		v.cb[0] += v.cb[1];
		(void)ftx_pixel(img, v.a.x, v.a.y, ((0xFF & (int)v.cr[0]) << 16) |
			((0xFF & (int)v.cg[0]) << 8) | (0xFF & (int)v.cb[0]));
	}
}

inline static void	sf_line0(t_image *img, t_ftx_line_data v, t_point color)
{
	v.cr[1] = (((color.y >> 16) & 0xFF) - v.cr[0]) / (v.d.x >> 1);
	v.cg[1] = (((color.y >> 8) & 0xFF) - v.cg[0]) / (v.d.x >> 1);
	v.cb[1] = ((color.y & 0xFF) - v.cb[0]) / (v.d.x >> 1);
	v.v = v.d.y - (v.d.x >> 1);
	while (v.a.x != v.b.x)
	{
		if (v.v >= 0)
		{
			v.a.y += v.s.y;
			v.v -= v.d.x;
		}
		v.a.x += v.s.x;
		v.v += v.d.y;
		v.cr[0] += v.cr[1];
		v.cg[0] += v.cg[1];
		v.cb[0] += v.cb[1];
		(void)ftx_pixel(img, v.a.x, v.a.y, ((0xFF & (int)v.cr[0]) << 16) |
			((0xFF & (int)v.cg[0]) << 8) | (0xFF & (int)v.cb[0]));
	}
}

t_image				*ftx_line(t_image *img, t_point a, t_point b, t_point color)
{
	t_ftx_line_data	v;

	if (a.x == b.x || a.y == b.y)
	{
		if (ft_point_equal(a, b))
			return (ftx_pixel(img, a.x, a.y, color.x));
		else if (a.x == b.x)
			return (ftx_vertical_line(img, a, b, color));
		else
			return (ftx_horizontal_line(img, a, b, color));
	}
	v.d = ft_point_substract(b, a);
	v.s = ft_point(SIGN(v.d.x), SIGN(v.d.y));
	v.d = ft_point(ABS(v.d.x) << 1, ABS(v.d.y) << 1);
	v.cr[0] = ((color.x >> 16) & 0xFF);
	v.cg[0] = ((color.x >> 8) & 0xFF);
	v.cb[0] = (color.x & 0xFF);
	v.a = a;
	v.b = b;
	(void)ftx_pixel(img, a.x, a.y, color.x);
	if (v.d.x > v.d.y)
		sf_line0(img, v, color);
	else
		sf_line1(img, v, color);
	return (img);
}
