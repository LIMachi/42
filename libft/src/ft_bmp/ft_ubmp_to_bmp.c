/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ubmp_to_bmp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 19:43:49 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/21 02:12:22 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** stores ubmp has standard 32 bites per pixels (with alpha) bitmaps
*/

inline static int	sf_ubmp_to_bmp(t_ubmp *ubmp, t_bitmap *out)
{
	int		i;
	int		j;

	if ((out->bmp = (unsigned char *)ft_memalloc(out->info.size_image)) == NULL)
		return (-1);
	j = -1;
	while (++j < ubmp->size.y && (i = -1))
		while (++i < ubmp->size.x)
			((int*)out->bmp)[j * ubmp->size.x + i] =
				ubmp->data[(ubmp->size.y - j - 1) * ubmp->size.x + i];
	return (0);
}

t_bitmap			*ft_ubmp_to_bmp(t_ubmp *ubmp)
{
	t_bitmap	*out;

	if (ubmp == NULL || ubmp->size.x < 1 || ubmp->size.y < 1 || ubmp->data ==
			NULL || ((out = (t_bitmap*)ft_memalloc(sizeof(t_bitmap))) == NULL))
		return (NULL);
	out->info.size_image = sizeof(unsigned char) * 4 * ubmp->size.x *
														ubmp->size.y;
	out->info.dib_size = 124;
	out->info.width = ubmp->size.x;
	out->info.height = ubmp->size.y;
	out->info.planes = 1;
	out->info.bit_count = 32;
	out->info.bit_compression = 3;
	out->info.x_pixels_meter = 1024;
	out->info.y_pixels_meter = 1024;
	out->info.colors_in_tab = 0;
	out->info.color_important = 0;
	out->info.alpha_bmask = 0xFF000000;
	out->info.red_bmask = 0x00FF0000;
	out->info.green_bmask = 0x0000FF00;
	out->info.blue_bmask = 0x000000FF;
	if (sf_ubmp_to_bmp(ubmp, out) == -1)
		return (ft_free(ubmp));
	return (out);
}
