/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_get_pixel_img.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 14:34:58 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/21 17:10:17 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <libftx.h>

int	ftx_get_pixel_img(t_image *img, const int x, const int y)
{
	if (!((img->endian == 0) ^ (LOCAL_ENDIAN == BIG_ENDIAN)))
		return (ft_bswap32(img->data[y * img->size.x + x]));
	return (img->data[y * img->size.x + x]);
}
