/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 09:40:29 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/30 17:42:30 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <mlx.h>

int			cb_exit(int k, int s, void *p)
{
	(void)p;
	if (k == KEY_EXIT && s == FTX_KEY_STATUS_PRESSED)
		ft_end(0);
	if (k == KEY_P && s == FTX_KEY_STATUS_PRESSED)
		cmd()->progress_bar_toggle ^= 1;
	return (0);
}

void		percent_callback(int percent, void *data)
{
	int y;
	int chunk;

	(void)data;
	if (cmd()->progress_bar_toggle)
	{
		y = 0;
		chunk = (int)(argn()->screen_size.x / 100);
		while (y < 16)
		{
			ftx_horizontal_line(ftx_data()->focused_window->vbuffer,
		ft_point(chunk * MAX(percent - 1, 0), y), ft_point(chunk * percent, y),
		ft_point(0xFF6619, 0xFF6619));
			y++;
		}
		if (percent % 1 == 0)
		{
			ftx_refresh_window(ftx_data()->focused_window);
			mlx_do_sync(ftx_data()->mlx);
		}
	}
}

void		update(int u)
{
	size_t size;

	if (u <= 0)
		return ;
	if (out()->data == NULL)
		init_output();
	size = out()->size.x * out()->size.y;
	ftocl_clear_current_kernel_arg(5);
	ftocl_set_current_kernel_arg(CL_MEM_READ_ONLY, 5, sizeof(t_camera),
			(void*)cam());
	ftocl_run_percent_callback(size, 9, percent_callback, NULL);
	ftocl_read_current_kernel_arg(0, out()->data);
	ftocl_read_current_kernel_arg(1, prim_map()->data);
	ftx_put_ubmp_img(ftx_data()->focused_window->vbuffer, ft_point(0, 0), out(),
		NOMASK);
	ftx_refresh_window(ftx_data()->focused_window);
}

int			keys_0(t_ftx_data *data, int i)
{
	if (data->keymap[KEY_LEFT].status == FTX_KEY_STATUS_PRESSED && ++i)
		rotate_cam(-0.05, cam()->origin_up);
	if (data->keymap[KEY_RIGHT].status == FTX_KEY_STATUS_PRESSED && ++i)
		rotate_cam(0.05, cam()->origin_up);
	if (data->keymap[KEY_UP].status == FTX_KEY_STATUS_PRESSED && ++i)
		rotate_cam(-0.05, cam()->origin_right);
	if (data->keymap[KEY_DOWN].status == FTX_KEY_STATUS_PRESSED && ++i)
		rotate_cam(0.05, cam()->origin_right);
	if (data->keymap[KEY_Q].status == FTX_KEY_STATUS_PRESSED && ++i)
		rotate_cam(-0.05, cam()->origin_dir);
	if (data->keymap[KEY_E].status == FTX_KEY_STATUS_PRESSED && ++i)
		rotate_cam(0.05, cam()->origin_dir);
	return (i);
}

int			keys(t_ftx_data *data)
{
	int i;

	i = 0;
	if (data->keymap[KEY_SHIFT_LEFT].status == FTX_KEY_STATUS_PRESSED && ++i)
		cam()->pos = cl_float4_sub(cam()->pos, cl_float4_scale(cam()->up, 10));
	if (data->keymap[KEY_SPACE].status == FTX_KEY_STATUS_PRESSED && ++i)
		cl_float4_p_add(&cam()->pos, cl_float4_scale(cam()->up, 10));
	if (data->keymap[KEY_D].status == FTX_KEY_STATUS_PRESSED && ++i)
		cl_float4_p_add(&cam()->pos, cl_float4_scale(cam()->right, 10));
	if (data->keymap[KEY_A].status == FTX_KEY_STATUS_PRESSED && ++i)
		cam()->pos =
			cl_float4_sub(cam()->pos, cl_float4_scale(cam()->right, 10));
	if (data->keymap[KEY_W].status == FTX_KEY_STATUS_PRESSED && ++i)
		cl_float4_p_add(&cam()->pos, cl_float4_scale(cam()->dir, 10));
	if (data->keymap[KEY_CTRL_LEFT].status == FTX_KEY_STATUS_PRESSED &&
			data->keymap[KEY_S].status == FTX_KEY_STATUS_PRESSED)
		ftx_screenshoot(ftx_data()->focused_window, NULL);
	else if (data->keymap[KEY_S].status == FTX_KEY_STATUS_PRESSED && ++i)
		cam()->pos = cl_float4_sub(cam()->pos, cl_float4_scale(cam()->dir, 10));
	update(keys_0(data, i));
	return (0);
}
