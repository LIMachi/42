/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 11:44:29 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/21 17:10:48 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <libftx.h>

t_image	*ftx_pixel(t_image *img, const int x, const int y, const int color)
{
	if (x < 0 || x >= img->size.x || y < 0 || y >= img->size.y)
		return (img);
	return (ftx_put_pixel_img(img, x, y, color));
}
