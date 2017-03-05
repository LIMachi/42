/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_quit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/28 14:29:59 by hmartzol          #+#    #+#             */
/*   Updated: 2017/03/02 12:52:35 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <connect_4.h>

void	ftx_quit(t_mlx mlx)
{
	int i;

	i = -1;
	while (++i < mlx.grid_size.y)
		free(mlx.grid[i]);
	free(mlx.grid);
	free(mlx.stop);
	mlx_destroy_image(mlx.ptr, mlx.img);
	mlx_destroy_window(mlx.ptr, mlx.win);
	exit(0);
}
