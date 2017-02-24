/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_put_pixel_img.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 11:52:50 by hmartzol          #+#    #+#             */
/*   Updated: 2016/02/27 18:04:35 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <connect_4.h>

void	ftx_put_pixel_img(t_mlx mlx, int x, int y, int color)
{
	int		i;

	if (x >= 0 && x < mlx.win_size.x && y >= 0 && y < mlx.win_size.y)
	{
		i = ((mlx.sl) * y) + (x * (mlx.bpp >> 3));
		if (mlx.endian)
		{
			mlx.data[i] = mlx_get_color_value(mlx.ptr, color >> 16);
			mlx.data[i + 1] = mlx_get_color_value(mlx.ptr, color >> 8);
			mlx.data[i + 2] = mlx_get_color_value(mlx.ptr, color);
		}
		else
		{
			mlx.data[i] = mlx_get_color_value(mlx.ptr, color);
			mlx.data[i + 1] = mlx_get_color_value(mlx.ptr, color >> 8);
			mlx.data[i + 2] = mlx_get_color_value(mlx.ptr, color >> 16);
		}
	}
}
