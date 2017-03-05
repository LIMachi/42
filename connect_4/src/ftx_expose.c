/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_expose.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 14:54:10 by hmartzol          #+#    #+#             */
/*   Updated: 2017/03/02 12:52:28 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <connect_4.h>

void	ftx_expose(void *param)
{
	t_mlx	mlx;

	mlx = *(t_mlx*)param;
	mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img, 0, 0);
}
