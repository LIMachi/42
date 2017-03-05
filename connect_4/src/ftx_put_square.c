/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_put_square.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/13 07:13:46 by hmartzol          #+#    #+#             */
/*   Updated: 2017/03/02 12:52:34 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <connect_4.h>

void	ftx_put_square(t_mlx mlx, t_pixel corner, t_point size)
{
	t_point pos;

	pos.y = corner.pos.y - 1;
	while (++pos.y < corner.pos.y + size.y &&
			!(0 * (pos.x = corner.pos.x - 1)))
		while (++pos.x < corner.pos.x + size.x)
			ftx_put_pixel_img(mlx, pos.x, pos.y, corner.color);
}
