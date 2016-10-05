/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_input_hooks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/15 09:10:16 by hmartzol          #+#    #+#             */
/*   Updated: 2016/07/15 09:15:13 by hmartzol         ###   ########.fr       */
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
		}
		else
			ft_putstr("OUT OF BOUNDS\n");
	}
	return (0);
}

int	ftx_keypress_hook(int key, void *p)
{
	t_mlx_data	*data;

	data = ftx_data(GDX_ACCES);
	ft_putnbr(((t_window*)p)->id);
	ft_putstr(" - Keypress: ");
	ft_putnbr(key);
	ft_putchar('\n');
	if (key == KEY_EXIT)
	{
		ftx_data(GDX_FREE);
		exit(0);
	}
	data->keymap[key] = 1;
	return (0);
}

int	ftx_keyrelease_hook(int key, void *p)
{
	t_mlx_data	*data;

	data = ftx_data(GDX_ACCES);
	ft_putnbr(((t_window*)p)->id);
	ft_putstr(" - Keyrelease: ");
	ft_putnbr(key);
	ft_putchar('\n');
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
