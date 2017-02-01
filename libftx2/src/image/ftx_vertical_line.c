/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_vertical_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 12:47:51 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/24 04:04:55 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <libftx.h>

inline static void	sf_vertical_line(t_image *img, t_point a, t_point b,
									t_point color)
{
	int		i;
	double	*c;
	int		l;
	int		d;

	d = b.y - a.y;
	l = ((b.y >= img->size.y) ? img->size.y - 1 : b.y) * img->size.x + a.x;
	c = (double[6]){((color.x >> 16) & 0xFF), ((color.x >> 8) & 0xFF),
					(color.x & 0xFF)};
	c = (double[6]){c[0], c[1], c[2], (((color.y & 0xFF0000) >> 16) - c[0]) / d,
		(((color.y & 0xFF00) >> 8) - c[1]) / d, ((color.y & 0xFF) - c[2]) / d};
	i = ((a.y < 0) ? -1 : a.y - 1) * img->size.x + a.x;
	while ((i += img->size.x) <= l)
	{
		c[0] += c[3];
		c[1] += c[4];
		c[2] += c[5];
		img->data[i] = ((0xFF & (int)c[0]) << 16) | ((0xFF & (int)c[1]) << 8) |
						(0xFF & (int)c[2]);
	}
}

t_image				*ftx_vertical_line(t_image *img, t_point a, t_point b,
															t_point color)
{
	if (a.x < 0 || a.x >= img->size.x)
		return (img);
	if (a.y > b.y)
	{
		ft_swapi(&(a.y), &(b.y));
		ft_swapi(&(color.x), &(color.y));
	}
	if (!((img->endian == 0) ^ (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)))
	{
		color.x = ft_bswap32(color.x);
		color.y = ft_bswap32(color.y);
	}
	sf_vertical_line(img, a, b, color);
	return (img);
}
