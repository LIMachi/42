/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_input_hooks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/15 09:10:16 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/31 16:23:46 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftx.h>

int	ftx_motion_hook(int x, int y, void *p)
{
	t_mlx_data	*data;
	t_window	*window;

	data = ftx_data(GDX_ACCES);
	window = (t_window*)p;
	if (window->id == data->focused_window)
	{
		ft_putnbr(window->id);
		ft_putstr(" - Motion: ");
		if (x >= 0 && x < window->size.x && y >= 0 && y < window->size.y)
		{
			ft_putnbr(x);
			ft_putstr(" ");
			ft_putnbr(y);
			ft_putchar('\n');
			data->mice.pos = ft_point(x, y);
			data->mice.joystick = ft_point((x > (2 * window->size.x / 3)) + 2 *
			(x > (4 * window->size.x / 5)) - (x < (window->size.x / 3)) - 2 *
			(x < (window->size.x / 5)), (y > (2 * window->size.y / 3)) + 2 *
			(y > (4 * window->size.y / 5)) - (y < (window->size.y / 3)) - 2 *
			(y < (window->size.y / 5)));
		}
	}
	return (0);
}

int	ftx_keypress_hook(int key, void *p)
{
	t_mlx_data	*data;

	data = ftx_data(GDX_ACCES);
	(void)p;
	free(ft_log(ft_itoa(((t_window*)p)->id)));
	(void)ft_log(" - Keypress: ");
	free(ft_log(ft_itoa(key)));
	(void)ft_log("\n");
	if (key == KEY_EXIT)
	{
		ftx_data(GDX_FREE);
		ft_end();
		exit(0);
	}
	data->keymap[key] = 1;
	return (0);
}

int	ftx_keyrelease_hook(int key, void *p)
{
	t_mlx_data	*data;

	data = ftx_data(GDX_ACCES);
	(void)p;
	free(ft_log(ft_itoa(((t_window*)p)->id)));
	(void)ft_log(" - Keyrelease: ");
	free(ft_log(ft_itoa(key)));
	(void)ft_log("\n");
	data->keymap[key] = 0;
	return (0);
}

int	ftx_buttonpress_hook(int key, int x, int y, void *p)
{
	t_mlx_data	*data;
	t_window	*window;

	data = ftx_data(GDX_ACCES);
	window = (t_window*)p;
	if (x >= 0 && x < window->size.x && y >= 0 && y < window->size.y)
	{
		ft_putnbr(window->id);
		data->focused_window = window->id;
		ft_putstr(" - Buttonpress: ");
		ft_putnbr(key);
		ft_putchar('\n');
		data->mice.map[key] = 1;
		if (key == 1)
			data->mice.drag = ft_point(x, y);
		ftx_motion_hook(x, y, p);
	}
	return (0);
}

int	ftx_buttonrelease_hook(int key, int x, int y, void *p)
{
	t_mlx_data	*data;
	t_window	*window;

	data = ftx_data(GDX_ACCES);
	window = (t_window*)p;
	ft_putnbr(window->id);
	ft_putstr(" - Buttonrelease: ");
	ft_putnbr(key);
	ft_putchar('\n');
	data->mice.map[key] = 0;
	ftx_motion_hook(x, y, p);
	return (0);
}
