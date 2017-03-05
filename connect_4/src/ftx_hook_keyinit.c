/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_hook_keyinit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 15:17:40 by hmartzol          #+#    #+#             */
/*   Updated: 2017/03/02 12:52:29 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <connect_4.h>

static int	sf_kpress(int keycode, void *param)
{
	((t_mlx *)param)->keymap[keycode] +=
		(((t_mlx *)param)->keymap[keycode] < MAX_TICK);
	return (0);
}

static int	sf_krelease(int keycode, void *param)
{
	((t_mlx *)param)->keymap[keycode] = 0;
	return (0);
}

void		ftx_hook_keyinit(t_mlx *obj)
{
	mlx_hook(obj->win, KEYPRESS, KEYPRESSMASK, sf_kpress, (void*)obj);
	mlx_hook(obj->win, KEYRELEASE, KEYRELEASEMASK, sf_krelease, (void*)obj);
}
