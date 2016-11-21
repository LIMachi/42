/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_refresh_window.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 09:28:39 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/21 17:14:48 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <mlx.h>
#include <libftx.h>

int	ftx_refresh_window(t_window *win)
{
	if (ftx_data()->mlx == NULL || win == NULL || win->vbuffer == NULL)
		return (-1);
	mlx_put_image_to_window(ftx_data()->mlx, win->win, win->vbuffer->img, 0, 0);
	return (0);
}
