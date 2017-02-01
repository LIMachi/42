/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bmp_to_ubmp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 19:43:49 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/26 07:05:22 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** can only do compression 0 and compression 3, it should work with most
** 8x8r8g8b, 8a8r8g8b, 0x8r8g8b, 0x5r6g5b and 1x5r5g5g bmp (32,24,16,15 bits)
** theorically can work with some 1,2,4 and 8 bits, but not all and not tested
*/

inline static uint32_t	sf_apply_mask(uint32_t value, uint32_t mask)
{
	uint32_t	i;

	if (mask == 0 || value == 0)
		return (0);
	i = value & mask;
	while (!(mask & 1))
	{
		i >>= 1;
		mask >>= 1;
	}
	if (mask >= 0xFF)
		return (i);
	else
		return ((uint32_t)(((double)0xFF) * (double)i / (double)mask));
}

inline static void		sf_bmp_to_ubmp(t_bitmap *bitmap, t_ubmp *out, t_point p,
									int x)
{
	int	t1;
	int	t2;
	int	y;

	t1 = (bitmap->info.height - p.y - 1) * bitmap->info.width + p.x;
	out->data[t1] = 0;
	y = -1;
	while (++y < 4)
		out->data[t1] += bitmap->bmp[p.y * x + p.x *
			(bitmap->info.bit_count >> 3) + y] << (8 * y);
	if (bitmap->info.bit_count < 32)
		out->data[t1] &= (0xFFFFFFFF >> (32 - bitmap->info.bit_count));
	if (bitmap->info.bit_compression == 3)
	{
		t1 = out->data[t1];
		t2 = (bitmap->info.alpha_bmask) ?
			sf_apply_mask(t1, bitmap->info.alpha_bmask) << 24 : 0xFF000000;
		t2 |= sf_apply_mask(t1, bitmap->info.red_bmask) << 16;
		t2 |= sf_apply_mask(t1, bitmap->info.green_bmask) << 8;
		t2 |= sf_apply_mask(t1, bitmap->info.blue_bmask);
		out->data[(bitmap->info.height - p.y - 1) * bitmap->info.width + p.x] =
																			t2;
	}
	else
		out->data[t1] |= 0xFF000000;
}

t_ubmp					*ft_bmp_to_ubmp(t_bitmap *bitmap)
{
	t_ubmp	*out;
	t_point	p;
	int		x;

	if (bitmap == NULL || ((out = (t_ubmp*)ft_malloc(sizeof(t_ubmp))) == NULL))
		return (NULL);
	out->size = (t_point){bitmap->info.width, bitmap->info.height};
	if ((out->data = (int*)ft_malloc(sizeof(int) * out->size.x * out->size.y))
			== NULL)
		return (ft_free(out));
	x = bitmap->info.width * (bitmap->info.bit_count >> 3);
	x += (ABS((int)sizeof(DWORD) - x) % sizeof(DWORD));
	p.y = bitmap->info.height;
	while (--p.y >= 0 && (p.x = -1))
		while (++p.x < x / (bitmap->info.bit_count >> 3))
			sf_bmp_to_ubmp(bitmap, out, p, x);
	return (out);
}
