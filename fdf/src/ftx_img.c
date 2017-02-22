/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_img.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/15 09:05:19 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/31 16:18:37 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftx.h>

/*
** void	ft_putpixelimg(void *mlx, t_image *img, t_point pos, int color)
** {
** 	int		i;
**
** 	i = ((img->size_line) * pos.y) + (pos.x * (img->bpp >> 3));
** 	if (img->endian)
** 	{
** 		img->data[i] = mlx_get_color_value(mlx, color >> 16);
** 		img->data[i + 1] = mlx_get_color_value(mlx, color >> 8);
** 		img->data[i + 2] = mlx_get_color_value(mlx, color);
** 	}
** 	else
** 	{
** 		img->data[i] = mlx_get_color_value(mlx, color);
** 		img->data[i + 1] = mlx_get_color_value(mlx, color >> 8);
** 		img->data[i + 2] = mlx_get_color_value(mlx, color >> 16);
** 	}
** }
*/

void		ftx_putpixelimg(t_image *img, t_point pos, int color)
{
	if (!((img->endian == 0) ^ (LOCAL_ENDIAN == BIG_ENDIAN)))
		img->data[pos.y * img->size.x + pos.x] = ft_bswap32(color);
	else
		img->data[pos.y * img->size.x + pos.x] = color;
}

void		ftx_put_img_to_img(t_image *out, t_image *img, unsigned int mask)
{
	t_point			pos;
	t_point			limit;
	t_point			d;
	unsigned int	t;

	if (out == NULL || img == NULL)
		return ;
	d = ft_point_substract(img->pos, out->pos);
	if (d.x >= out->size.x || d.x >= out->size.x || d.x + img->size.x < 0 ||
		d.y + img->size.y < 0)
		return ;
	if (mask != NOMASK && !((img->endian == 0) ^ (LOCAL_ENDIAN == BIG_ENDIAN)))
		mask = ft_bswap32(mask);
	limit.x = (d.x + img->size.x >= out->size.x) ? out->size.x : img->size.x;
	limit.y = (d.y + img->size.y >= out->size.y) ? out->size.y : img->size.y;
	pos.y = ((d.y > 0) ? -1 : -d.y - 1);
	while (++pos.y < limit.y && !(0 & (pos.x = ((d.x > 0) ? -1 : -d.x - 1))))
		while (++pos.x < limit.x)
		{
			t = (unsigned int)img->data[pos.y * img->size.x + pos.x];
			if (out->endian != img->endian)
				t = ft_bswap32(t);
			if (mask == NOMASK || t != mask)
				out->data[(pos.y + d.y) * out->size.x + pos.x + d.x] = t;
		}
}

void		ftx_clear_img(t_image *img)
{
	int x;
	int y;
	int t;

	if (img == NULL)
		return ;
	y = -img->size.x;
	t = (img->size.x - 1) * img->size.y;
	while ((y += img->size.x) < t)
	{
		x = -1;
		while (++x < img->size.x)
			img->data[y + x] = 0;
	}
}

void		ftx_fill_image(t_image *img)
{
	int x;
	int y;
	int w;
	int h;
	int color;

	w = img->size.x;
	h = img->size.y;
	x = w;
	while (--x)
	{
		y = img->size.y;
		while (--y)
		{
			color = (x * 255) / w + ((((w - x) * 255) / w) << 16)
										+ (((y * 255) / h) << 8);
			ftx_putpixelimg(img, ft_point(x, y), color);
		}
	}
}
