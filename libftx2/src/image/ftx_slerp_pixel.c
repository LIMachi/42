/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_slerp_pixel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 14:32:51 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/21 17:11:11 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <libftx.h>

t_image	*ftx_slerp_pixel(t_image *img, const t_point pos, const int color,
						const double value)
{
	if (value == 1.0)
		return (ftx_put_pixel_img(img, pos.x, pos.y, color));
	if (value == 0.0)
		return (img);
	return (ftx_put_pixel_img(img, pos.x, pos.y, ftx_color_lerp(color,
								ftx_get_pixel_img(img, pos.x, pos.y), value)));
}
