/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_hook_mice.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 09:51:11 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/24 11:00:02 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <mlx.h>
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
	t_mice	*m;

	m = (t_mice*)p;
	if (x < 0 || y < 0 || x >= ftx_data()->focused_window->size.x
			|| y >= ftx_data()->focused_window->size.y)
		return (0);
	m->pos = ft_point(x, y);
	if (m->callback != NULL)
		return (m->callback(m->pos, m->click_pos, m->data));
	return (0);
}

static int	sf_button_press_hook(int key, int x, int y, void *p)
{
	t_key_data	*k;
	t_mice		*m;

	if (x < 0 || y < 0 || x >= ((t_window*)p)->size.x
			|| y >= ((t_window*)p)->size.y)
		return (0);
	ftx_data()->focused_window = (t_window*)p;
	m = &((t_window*)p)->mice;
	m->pos = ft_point(x, y);
	m->click_pos = ft_point(x, y);
	k = &m->keymap[key];
	k->status = FTX_KEY_STATUS_PRESSED;
	k->tick = ftx_data()->tick;
	if (k->callback != NULL)
		return (k->callback(key, k->status, k->data));
	return (0);
}

static int	sf_button_release_hook(int key, int x, int y, void *p)
{
	t_key_data	*k;

	if (x < 0 || y < 0 || x >= ftx_data()->focused_window->size.x
			|| y >= ftx_data()->focused_window->size.y)
		return (0);
	((t_mice*)p)->pos = ft_point(x, y);
	k = &((t_mice*)p)->keymap[key];
	k->status = FTX_KEY_STATUS_RELEASED;
	k->tick = ftx_data()->tick;
	if (k->callback != NULL)
		return (k->callback(key, k->status, k->data));
	((t_mice*)p)->click_pos = ft_point(!0, !0);
	return (0);
}

int			ftx_hook_mice_move(t_window *window, int (*callback)(t_point pos,
								t_point click_pos, void *data), void *data)
{
	t_mice	*mice;

	if (window == NULL)
	{
		ft_error(EINVAL, "ftx_hook_mice_move got NULL parameter\n");
		return (-1);
	}
	mice = &window->mice;
	mice->pos = ft_point(!0, !0);
	mice->click_pos = ft_point(!0, !0);
	mice->callback = callback;
	mice->data = data;
	mlx_hook(window->win, 6, (1L << 6), &sf_motion_hook, (void*)mice);
	return (0);
}

int			ftx_hook_mice_button(t_window *window, int button,
				int (*callback)(int key, int status, void *data), void *data)
{
	t_key_data	*k;

	if (window == NULL)
	{
		ft_error(EINVAL, "ftx_hook_mice_button got NULL parameter\n");
		return (-1);
	}
	if (button < 0 || button >= 10)
	{
		ft_error(EINVAL, "ftx_hook_mice_button got invalid button parameter\n");
		return (-1);
	}
	k = &window->mice.keymap[button];
	k->status = FTX_KEY_STATUS_RELEASED;
	k->tick = !0u;
	k->callback = callback;
	k->data = data;
	mlx_hook(window->win, 4, (1L << 2), &sf_button_press_hook,
				(void*)window);
	mlx_hook(window->win, 5, (1L << 3), &sf_button_release_hook,
				(void*)&window->mice);
	return (0);
}
