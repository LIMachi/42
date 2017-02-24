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
	out->info = (t_dib_header){.dib_size = 56, .width = ubmp->size.x,
		.height = ubmp->size.y, .planes = 1, .bit_count = 32,
		.bit_compression = 3, .size_image = 4 * ubmp->size.x * ubmp->size.y,
		.x_pixels_meter = 3777, .y_pixels_meter = 3777, .colors_in_tab = 0,
		.color_important = 0, .red_bmask = 0xFF0000, .green_bmask = 0xFF00,
		.blue_bmask = 0xFF, .alpha_bmask = 0xFF000000};
	if (sf_ubmp_to_bmp(ubmp, out) == -1)
		return (ft_free(ubmp));
	return (out);
}
