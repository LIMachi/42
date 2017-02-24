/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_put_pixel_img.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 11:42:41 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/21 17:11:00 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <libftx.h>

t_image	*ftx_put_pixel_img(t_image *img, const int x, const int y, int color)
{
	if (!((img->endian == 0) ^ (LOCAL_ENDIAN == BIG_ENDIAN)))
		img->data[y * img->size.x + x] = ft_bswap32(color);
	else
		img->data[y * img->size.x + x] = color;
	return (img);
}
