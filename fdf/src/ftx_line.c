/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/15 00:22:19 by hmartzol          #+#    #+#             */
/*   Updated: 2016/08/28 19:25:03 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftx.h>
#include <stdio.h>

int		ftx_fixtorgb(t_fix r, t_fix g, t_fix b)
{
	return ((((r.FIX_INT) & 0xFF) << 16) | (((g.FIX_INT) & 0xFF) << 8) |
			(((b.FIX_INT) & 0xFF)));
}

int		ft_ptequal(t_point a, t_point b)
{
	return (a.x == b.x && a.y == b.y);
}

void	ftx_pixel(t_image *img, int x, int y, int color)
{
	if (img == NULL || x < 0 || x >= img->size.x || y < 0
		|| y >= img->size.y)
		return ;
	ftx_putpixelimg(img, ft_point(x, y), color);
}

void	ft_swapint(int *a, int *b)
{
	int t;

	t = *a;
	*a = *b;
	*b = t;
}

/*
** legacy version
*/

/*
void	ftx_horizontal_line(t_image *img, t_point a, t_point b, t_point color)
{
	int			i;
	int			l;
	int			c;

	if (a.y < 0 || a.y >= img->size.y)
		return ;
	if (a.x > b.x)
	{
		ft_swapint(&(a.x), &(b.x));
		ft_swapint(&(color.y), &(color.x));
	}
	i = (a.x < 0) ? -1 : a.x - 1;
	l = (b.x >= img->size.x) ?
		img->size.x - 1 : b.x;
	c = color.x;
	while (++i <= l)
	{
		if (color.x != color.y)
			c = sf_color_mix(color.x, color.y, (t_fix){(((i - a.x) << 16)
										/ (b.x - a.x))});
		ftx_putpixelimg(img, ft_point(i, a.y), c);
	}
}
*/

/*
** optimised version (but yep, ugly like your mom)
*/

void	ftx_horizontal_line(t_image *img, t_point a, t_point b, t_point color)
{
	int			i;
	int			l;
	t_fix		*c;
	int			d;

	if (a.y < 0 || a.y >= img->size.y)
		return ;
	if (a.x > b.x)
	{
		ft_swapint(&(a.x), &(b.x));
		ft_swapint(&(color.x), &(color.y));
	}
	d = b.x - a.x;
	if (!((img->endian == 0) ^ (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)))
	{
		color.x = ft_bswap32(color.x);
		color.y = ft_bswap32(color.y);
	}
	l = a.y * img->size.x + ((b.x >= img->size.x) ?	img->size.x - 1 : b.x);
	c = (t_fix[6]){{.FIX_INT = ((color.x >> 16) & 0xFF)}, {.FIX_INT = ((color.x
		>> 8) & 0xFF)}, {.FIX_INT = (color.x & 0xFF)}};
	c = (t_fix[6]){c[0], c[1], c[2], {.i32 = ((color.y & 0xFF0000) - c[0].i32)
		/ d}, {.i32 = (((color.y & 0xFF00) << 8) - c[1].i32) / d},
		{.i32 = (((color.y & 0xFF) << 16) - c[2].i32) / d}};
	i = a.y * img->size.x + ((a.x < 0) ? -1 : a.x - 1);
	while (++i <= l)
	{
		c[0].i32 += c[3].i32;
		c[1].i32 += c[4].i32;
		c[2].i32 += c[5].i32;
		img->data[i] = ftx_fixtorgb(c[0], c[1], c[2]);
	}
}

/*
** legacy version
*/

/*
void	ftx_vertical_line(t_image *img, t_point a, t_point b, t_point color)
{
	int			i;
	int			l;
	int			c;

	if (a.x < 0 || a.x >= img->size.x)
		return ;
	if (a.y > b.y)
	{
		ft_swapint(&(a.y), &(b.y));
		ft_swapint(&(color.x), &(color.y));
	}
	i = (a.y < 0) ? -1 : a.y - 1;
	l = (b.y >= img->size.y) ?
		img->size.y - 1 : b.y;
	c = color.x;
	while (++i <= l)
	{
		if (color.x != color.y)
			c = sf_color_mix(color.x, color.y, (t_fix){(((i - a.y) << 16)
										/ (b.y - a.y))});
		ftx_putpixelimg(img, ft_point(a.x, i), c);
	}
}
*/

/*
** optimised version (but yep, ugly like your mom)
*/

void	ftx_vertical_line(t_image *img, t_point a, t_point b, t_point color)
{
	int			i;
	int			l;
	t_fix		*c;
	int			d;

	if (a.x < 0 || a.x >= img->size.x)
		return ;
	if (a.y > b.y)
	{
		ft_swapint(&(a.y), &(b.y));
		ft_swapint(&(color.x), &(color.y));
	}
	d = b.y - a.y;
	if (!((img->endian == 0) ^ (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)))
	{
		color.x = ft_bswap32(color.x);
		color.y = ft_bswap32(color.y);
	}
	l = ((b.y >= img->size.y) ?	img->size.y - 1 : b.y) * img->size.x + a.x;
	c = (t_fix[6]){{.FIX_INT = ((color.x >> 16) & 0xFF)}, {.FIX_INT = ((color.x
		>> 8) & 0xFF)}, {.FIX_INT = (color.x & 0xFF)}};
	c = (t_fix[6]){c[0], c[1], c[2], {.i32 = ((color.y & 0xFF0000) - c[0].i32)
		/ d}, {.i32 = (((color.y & 0xFF00) << 8) - c[1].i32) / d},
		{.i32 = (((color.y & 0xFF) << 16) - c[2].i32) / d}};
	i = ((a.y < 0) ? -1 : a.y - 1) * img->size.x + a.x;
	while ((i += img->size.x) <= l)
	{
		c[0].i32 += c[3].i32;
		c[1].i32 += c[4].i32;
		c[2].i32 += c[5].i32;
		img->data[i] = ftx_fixtorgb(c[0], c[1], c[2]);
	}
}

t_fixpoint	ft_fixpoint(int x, int y)
{
	t_fixpoint	out;

	out.x.i32 = x;
	out.y.i32 = y;
	return (out);
}

/*
** legacy version
*/


void	ftx_line(t_image *img, t_point a, t_point b, t_point color)
{
	t_vtff_la_norme_0	v;

	if (a.x == b.x || a.y == b.y)
	{
		if (ft_ptequal(a, b))
			ftx_pixel(img, a.x, a.y,
							sf_color_mix(color.x, color.y, (t_fix){1 << 15}));
		else if (a.x == b.x)
			ftx_vertical_line(img, a, b, color);
		else
			ftx_horizontal_line(img, a, b, color);
		return ;
	}
	v.d = ft_point(b.x - a.x, b.y - a.y);
	v.s = ft_point(SIGN(v.d.x), SIGN(v.d.y));
	v.d = ft_point(ABS(v.d.x) << 1, ABS(v.d.y) << 1);
	v.cr[0].FIX_INT = ((color.x >> 16) & 0xFF);
	v.cg[0].FIX_INT = ((color.x >> 8) & 0xFF);
	v.cb[0].FIX_INT = (color.x & 0xFF);
	v.a = a;
	v.b = b;
	ftx_pixel(img, v.a.x, v.a.y, color.x);
	if (v.d.x > v.d.y)
	{
		v.cr[1].i32 = ((((color.y >> 16) & 0xFF) << 16) - v.cr[0].i32)
															/ (v.d.x >> 1);
		v.cg[1].i32 = ((((color.y >> 8) & 0xFF) << 16) - v.cg[0].i32) / (v.d.x >> 1);
		v.cb[1].i32 = (((color.y & 0xFF) << 16) - v.cb[0].i32) / (v.d.x >> 1);
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
			v.cr[0].i32 += v.cr[1].i32;
			v.cg[0].i32 += v.cg[1].i32;
			v.cb[0].i32 += v.cb[1].i32;
			ftx_pixel(img, v.a.x, v.a.y, ftx_fixtorgb(v.cr[0], v.cg[0], v.cb[0]));
		}
	}
	else
	{
		v.cr[1].i32 = ((((color.y >> 16) & 0xFF) << 16) - v.cr[0].i32)
															/ (v.d.y >> 1);
		v.cg[1].i32 = ((((color.y >> 8) & 0xFF) << 16) - v.cg[0].i32) / (v.d.y >> 1);
		v.cb[1].i32 = (((color.y & 0xFF) << 16) - v.cb[0].i32) / (v.d.y >> 1);
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
			v.cr[0].i32 += v.cr[1].i32;
			v.cg[0].i32 += v.cg[1].i32;
			v.cb[0].i32 += v.cb[1].i32;
			ftx_pixel(img, v.a.x, v.a.y, ftx_fixtorgb(v.cr[0], v.cg[0], v.cb[0]));
		}
	}
}


/*
** optimised version (but yep, ugly like your mom)
*/

/*
void	ftx_line(t_image *img, t_point a, t_point b, t_point color)
{
	t_vtff_la_norme_0	v;

	if (a.x == b.x || a.y == b.y)
	{
		if (ft_ptequal(a, b))
			ftx_pixel(img, a.x, a.y,
							sf_color_mix(color.x, color.y, (t_fix){1 << 15}));
		else if (a.x == b.x)
			ftx_vertical_line(img, a, b, color);
		else
			ftx_horizontal_line(img, a, b, color);
		return ;
	}
	if (!((img->endian == 0) ^ (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)))
	{
		color.x = ft_bswap32(color.x);
		color.y = ft_bswap32(color.y);
	}
	v.d = ft_point(b.x - a.x, b.y - a.y);
	v.s = ft_point(SIGN(v.d.x), SIGN(v.d.y));
	v.d = ft_point(ABS(v.d.x) << 1, ABS(v.d.y) << 1);
	v.cr[0].FIX_INT = ((color.x >> 16) & 0xFF);
	v.cg[0].FIX_INT = ((color.x >> 8) & 0xFF);
	v.cb[0].FIX_INT = (color.x & 0xFF);
	v.a = a;
	v.b = b;
	if (v.a.x >= 0 && v.a.y >= 0 && v.a.x < img->size.x
			&& v.a.y < img->size.y)
		img->data[v.a.x + v.a.y * img->size.x] = color.x;
	if (v.d.x > v.d.y)
	{
		v.cr[1].i32 = ((((color.y >> 16) & 0xFF) << 16) - v.cr[0].i32)
															/ (v.d.x >> 1);
		v.cg[1].i32 = ((((color.y >> 8) & 0xFF) << 16) - v.cg[0].i32) / (v.d.x >> 1);
		v.cb[1].i32 = (((color.y & 0xFF) << 16) - v.cb[0].i32) / (v.d.x >> 1);
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
			v.cr[0].i32 += v.cr[1].i32;
			v.cg[0].i32 += v.cg[1].i32;
			v.cb[0].i32 += v.cb[1].i32;
			if (v.a.x >= 0 && v.a.y >= 0 && v.a.x < img->size.x
					&& v.a.y < img->size.y)
				img->data[v.a.x + v.a.y * img->size.x] =
					ftx_fixtorgb(v.cr[0], v.cg[0], v.cb[0]);
		}
	}
	else
	{
		v.cr[1].i32 = ((((color.y >> 16) & 0xFF) << 16) - v.cr[0].i32)
															/ (v.d.y >> 1);
		v.cg[1].i32 = ((((color.y >> 8) & 0xFF) << 16) - v.cg[0].i32) / (v.d.y >> 1);
		v.cb[1].i32 = (((color.y & 0xFF) << 16) - v.cb[0].i32) / (v.d.y >> 1);
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
			v.cr[0].i32 += v.cr[1].i32;
			v.cg[0].i32 += v.cg[1].i32;
			v.cb[0].i32 += v.cb[1].i32;
			if (v.a.x >= 0 && v.a.y >= 0 && v.a.x < img->size.x
					&& v.a.y < img->size.y)
				img->data[v.a.x + v.a.y * img->size.x] =
					ftx_fixtorgb(v.cr[0], v.cg[0], v.cb[0]);
		}
	}
}
*/

//void	ftx_circle()
//{
//
//}

/*
** symetric star idea: take a number of branch, inner size and outer size in
** parameter, make 2 (virtual circle), and every 360 / (2 * nb_branch), put a
** (virutal pixel), once finished (or while doing it), link the pixels together
*/

//void	ftx_star(t_image *img, t_point pos, int nb_branch, t_point size)
//{

//}
