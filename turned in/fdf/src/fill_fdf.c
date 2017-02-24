/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 08:42:49 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/02 12:38:44 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftx.h>

inline static int		sf_update_rotation(t_fdf *fdf, t_mlx_data *data)
{
	int		up;
	double	tmp;

	up = 0;
	if (data->mice.joystick.y && (up = 1))
	{
		tmp = (0.01 * -data->mice.joystick.y) / 2;
		fdf->camera.object.orientation = ft_quat_multiply(
	fdf->camera.object.orientation, ft_quat(ft_cos(tmp), ft_sin(tmp), 0, 0));
	}
	if (data->mice.joystick.x && (up = 1))
	{
		tmp = (0.01 * data->mice.joystick.x) / 2;
		fdf->camera.object.orientation = ft_quat_multiply(
	fdf->camera.object.orientation, ft_quat(ft_cos(tmp), 0, ft_sin(tmp), 0));
	}
	if ((data->keymap[KEY_Q] || data->keymap[KEY_E]) && (up = 1))
	{
		tmp = (0.05 * (data->keymap[KEY_E] - data->keymap[KEY_Q])) / 2;
		fdf->camera.object.orientation = ft_quat_multiply(
	fdf->camera.object.orientation, ft_quat(ft_cos(tmp), 0, 0, ft_sin(tmp)));
	}
	return (up);
}

inline static int		sf_update_position(t_fdf *fdf, t_mlx_data *data, int up)
{
	if (data->keymap[KEY_D] && (up |= 2))
		fdf->camera.object.position =
			ft_vector_add(fdf->camera.object.position,
			ft_vector_scale(fdf->camera.object.axis_x, SPEED));
	if (data->keymap[KEY_A] && (up |= 2))
		fdf->camera.object.position =
			ft_vector_add(fdf->camera.object.position,
			ft_vector_scale(fdf->camera.object.axis_x, -SPEED));
	if (data->keymap[KEY_SHIFT_LEFT] && (up |= 2))
		fdf->camera.object.position =
			ft_vector_add(fdf->camera.object.position,
			ft_vector_scale(fdf->camera.object.axis_y, SPEED));
	if (data->keymap[KEY_SPACE] && (up |= 2))
		fdf->camera.object.position =
			ft_vector_add(fdf->camera.object.position,
			ft_vector_scale(fdf->camera.object.axis_y, -SPEED));
	if (data->keymap[KEY_W] && (up |= 2))
		fdf->camera.object.position =
			ft_vector_add(fdf->camera.object.position,
			ft_vector_scale(fdf->camera.object.axis_z, SPEED));
	if (data->keymap[KEY_S] && (up |= 2))
		fdf->camera.object.position =
			ft_vector_add(fdf->camera.object.position,
			ft_vector_scale(fdf->camera.object.axis_z, -SPEED));
	return (up);
}

int						fill_fdf(t_window *win, t_image *img)
{
	t_fdf			*fdf;
	t_mlx_data		*data;
	int				up;

	data = ftx_data(GDX_ACCES);
	fdf = (t_fdf*)(win->data);
	if (data->focused_window == win->id)
	{
		up = sf_update_rotation(fdf, data);
		up = sf_update_position(fdf, data, up);
		if (data->keymap[KEY_PAD_0] && (up = 1))
		{
			fdf->camera.object.position = ft_vector(0, 0, 600);
			fdf->camera.object.orientation = ft_quat(1, 0, 0, 0);
			fdf->camera.object.axis_x = ft_vector(1, 0, 0);
			fdf->camera.object.axis_y = ft_vector(0, 1, 0);
			fdf->camera.object.axis_z = ft_vector(0, 0, 1);
			fdf->camera.frustrum = fdf->camera.frustrum_origin;
			win->zoom = 10;
		}
		if (up)
			sf_update(up, fdf, img, win);
	}
	img->update = 1;
	return (0);
}
