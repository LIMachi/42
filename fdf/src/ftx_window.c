/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/15 08:31:07 by hmartzol          #+#    #+#             */
/*   Updated: 2016/07/15 08:37:06 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftx.h>

t_window	*ftx_get_window(int id)
{
	t_mlx_data	*data;
	t_window	*tmp;

	data = ftx_data(GDX_ACCES);
	if (data->windows == NULL)
		return (NULL);
	tmp = data->windows;
	while (tmp != NULL && tmp->id != id)
		tmp = tmp->next;
	if (tmp && tmp->id == id)
		return (tmp);
	tmp = data->windows->prev;
	while (tmp != NULL && tmp->id != id)
		tmp = tmp->prev;
	if (tmp && tmp->id == id)
		return (tmp);
	return (NULL);
}

int		ftx_free_all_windows(t_window *win)
{
	void		*mlx;
	t_window	*tmp;

	if (!ftx_data(GDX_ACCES) || !(mlx = ftx_data(GDX_ACCES)->mlx))
		return (-1);
	if (win == NULL)
		return (1);
	while (win->next)
		win = win->next;
	tmp = win;
	while (tmp)
	{
		tmp = win->prev;
		if (win->win)
			mlx_destroy_window(mlx, win->win);
		if (win->vbuffer)
			ftx_free_image(win->vbuffer);
		if (win->images)
			ftx_free_all_images(win->images);
		free(win);
	}
	return (0);
}

int		ftx_free_window(t_window *win)
{
	void	*mlx;

	if (!ftx_data(GDX_ACCES) || !(mlx = ftx_data(GDX_ACCES)->mlx))
		return (-1);
	if (win == NULL)
		return (1);
	(void)(win->win && mlx_destroy_window(mlx, win->win));
	(void)(win->vbuffer && ftx_free_image(win->vbuffer));
	if (win->images)
		ftx_free_all_images(win->images);
	if (win->next)
	{
		if (win->prev)
		{
			win->prev->next = win->next;
			win->next->prev = win->prev;
		}
		else
			win->next->prev = NULL;
	}
	else
		if (win->prev)
			win->prev->next = NULL;
	free(win);
	return (0);
}

t_window	*ftx_new_window(t_point size, char *name, int wfps)
{
	t_window	*window;
	void		*mlx;
	int			error;

	if ((window = (t_window*)ft_memalloc(sizeof(t_window))) == NULL)
		return (NULL);
	error = !ftx_data(GDX_ACCES) || !(mlx = ftx_data(GDX_ACCES)->mlx);
	error = error || !(window->win = mlx_new_window(mlx, size.x, size.y, name));
	if (!error)
		window->size = size;
	error = error || !(window->vbuffer = ftx_new_image(size));
	if (!error)
	{
		window->wfps = wfps;
		window->zoom = 1;
	}
	else
	{
		if (window->win)
			mlx_destroy_window(mlx, window->win);
		if (window->vbuffer)
			ftx_free_image(window->vbuffer);
		ft_memdel((void**)window);
	}
	return (window);
}

int		ftx_add_window(t_window *win)
{
	t_mlx_data	*data;
	t_window	*tmp;
	static int	gid = 0;

	data = ftx_data(GDX_ACCES);
	++gid;
	win->id = gid;
	if (data->windows == NULL)
		data->windows = win;
	else
	{
		tmp = data->windows;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = win;
	}
	return (gid);
}
