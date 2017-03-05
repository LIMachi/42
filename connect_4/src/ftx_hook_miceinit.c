/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_hook_miceinit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 15:17:40 by hmartzol          #+#    #+#             */
/*   Updated: 2017/03/02 12:52:32 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <connect_4.h>

static int	sf_motion(int x, int y, void *param)
{
	((t_mlx *)param)->micemap[0] = x;
	((t_mlx *)param)->micemap[1] = y;
	return ((int)(size_t)param);
}

static int	sf_mpress(int button, int x, int y, void *param)
{
	((t_mlx *)param)->micemap[1 + button] +=
		(((t_mlx *)param)->micemap[1 + button] < 100000);
	return (sf_motion(x, y, param));
}

static int	sf_mrelease(int button, int x, int y, void *param)
{
	((t_mlx *)param)->micemap[1 + button] = 0;
	return (sf_motion(x, y, param));
}

void		ftx_hook_miceinit(t_mlx *obj)
{
	mlx_hook(obj->win, BUTTONPRESS, BUTTONPRESSMASK, sf_mpress, (void*)obj);
	mlx_hook(obj->win, BUTTONRELEASE, BUTTONRELEASEMASK, sf_mrelease,
			(void*)obj);
	mlx_hook(obj->win, MOTIONNOTIFY, POINTERMOTIONMASK, sf_motion, (void*)obj);
}
