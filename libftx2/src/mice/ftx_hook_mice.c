/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_hook_mice.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 09:51:11 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/17 11:09:13 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftx.h>

/*
** t_mice is a structure containing most information about the mice
*/

/*
** the tick system is bassed on the refreshing of the screen, so 60 tick per
** second if the screen is capped at 60 fps, but can be much more or even less
*/

/*
** if time.h is included, the tick system will be forced at 60 tick per second
*/

static int	sf_motion_hook(int x, int y, void *p)
{
	((t_window*)((void**)p)[0])->mice.pos = ft_point(x, y);
	return (((int (*)(void *data))((void**)p)[1])(((void**)p)[2]));
}

static int	sf_button_press_hook(int key, int x, int y, void *p)
{
	t_mice	*mice;

	mice = &((t_window*)((void**)p)[0])->mice;
	mice->pos = ft_point(x, y);
	mice->click_pos = ft_point(x, y);
	mice->click_tick = ftx_data()->tick;
	mice->click_button ^= 1 << key;
	return (((int (*)(void *data))((void**)p)[1])(((void**)p)[2]));
}

static int	sf_button_release_hook(int key, int x, int y, void *p)
{
	t_mice	*mice;

	mice = &((t_window*)((void**)p)[0])->mice;
	mice->pos = ft_point(x, y);
	mice->click_pos = ft_point(!0, !0);
	mice->click_tick = !0u;
	mice->last_click_release = ftx_data()->tick;
	mice->click_button ^= 1 << key;
	return (((int (*)(void *data))((void**)p)[1])(((void**)p)[2]));
}

int			ftx_hook_mice(t_window *window, int (*mice_update_func)(void *data),
 							void *data)
{
	void	*tmp[3];

	if (window == NULL || mice_update_func == NULL)
	{
		ft_error(EINVAL, "ftx_hook_mice got NULL parameters\n");
		return (-1);
	}
	tmp[0] = (void*)window;
	tmp[1] = (void*)mice_update_func;
	tmp[2] = data;
	window->mice = (t_mice){.pos = ft_point(!0, !0),
							.click_pos = ft_point(!0, !0),
							.click_tick = !0,
							.last_click_release = 0,
							.click_button = 0};
	mlx_hook(window->win, 4, (1L << 2), &sf_button_press_hook, (void*)tmp);
	mlx_hook(window->win, 5, (1L << 3), &sf_button_release_hook, (void*)tmp);
	mlx_hook(window->win, 6, (1L << 6), &sf_motion_hook, (void*)tmp);
	return (0);
}
