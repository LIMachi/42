/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 12:48:34 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/02 12:48:48 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftx.h>

void	ftx_pixel(t_image *img, int x, int y, int color)
{
	if (img == NULL || x < 0 || x >= img->size.x || y < 0
		|| y >= img->size.y)
		return ;
	ftx_putpixelimg(img, ft_point(x, y), color);
}
