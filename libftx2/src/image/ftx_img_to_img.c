/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_img_to_img.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 11:58:05 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/21 17:10:15 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <libftx.h>

t_image	*ftx_img_to_img(t_image *out, const t_point pos, const t_image *img,
							int mask)
{
	t_point	posi;
	t_point	l;
	int		t;

	if (out == NULL || img == NULL)
		return (out);
	if (pos.x >= out->size.x || pos.x >= out->size.x || pos.x + img->size.x < 0
			|| pos.y + img->size.y < 0)
		return (out);
	if (mask != NOMASK && !((img->endian == 0) ^ (LOCAL_ENDIAN == BIG_ENDIAN)))
		mask = ft_bswap32(mask);
	l.x = (pos.x + img->size.x >= out->size.x) ? out->size.x : img->size.x;
	l.y = (pos.y + img->size.y >= out->size.y) ? out->size.y : img->size.y;
	posi.y = ((pos.y > 0) ? -1 : -pos.y - 1);
	while (++posi.y < l.y && !(0 & (posi.x = ((pos.x > 0) ? -1 : -pos.x - 1))))
		while (++posi.x < l.x)
		{
			t = (unsigned int)img->data[posi.y * img->size.x + posi.x];
			if (out->endian != img->endian)
				t = ft_bswap32(t);
			if (mask == NOMASK || t != mask)
				out->data[(posi.y + pos.y) * out->size.x + posi.x + pos.x] = t;
		}
	return (out);
}
