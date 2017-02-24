/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 18:02:28 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/21 19:23:01 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftocl.h>
#include <libftx.h>
#include <fractol.h>

int		refresh_fractol_window(t_window *win)
{
	static t_fractol_data	*data = NULL;
	int						x;
	int						y;
	t_image					*img;

	if (data == NULL)
		data = fractol_data();
	img = win->vbuffer;
	ftocl_start_current_kernel(1, &data->array_size, NULL);
	ftocl_read_current_kernel_arg(1, data->rbmp);
	y = -1;
	while (++y < data->args.size.y && (x = -1))
		while (++x < data->args.size.x)
			ftx_put_pixel_img(img, x, y, data->rbmp[y * data->args.size.x + x]);
	if (*ftx_button_status(MICE_LEFT) == FTX_KEY_STATUS_PRESSED)
		ftx_put_selection_square(img, win->mice.pos, win->mice.click_pos,
									0x7777FF);
	if (data->info)
		print_info(data, img);
	ftx_refresh_window(win);
	return (0);
}

void	first_args(void)
{
	t_fractol_data	*data;

	data = fractol_data();
	ftocl_set_current_kernel_arg(CL_MEM_READ_ONLY, 0, sizeof(t_fractol_args),
												&data->args);
	ftocl_set_current_kernel_arg(CL_MEM_WRITE_ONLY, 1, data->array_size, NULL);
	refresh_fractol_window(ftx_data()->focused_window);
}

int		call_exit(int key, int status, void *data)
{
	(void)data;
	if (key == KEY_EXIT && status == FTX_KEY_STATUS_PRESSED)
		exit(0);
	return (0);
}

void	fractol(void)
{
	t_window		*win;

	if ((win = ftx_new_window(ft_point(WIDTH, HEIGHT), "fractol",
								(const uint64_t *)"fractol")) == NULL)
		return ;
	ftx_key_hook(KEY_EXIT, &call_exit, NULL);
	ftx_key_hook(KEY_R, &call_key_0, fractol_data());
	ftx_key_hook(KEY_S, &call_key_0, fractol_data());
	ftx_key_hook(KEY_L, &call_key_0, fractol_data());
	ftx_key_hook(KEY_LEFT, &call_key_2, fractol_data());
	ftx_key_hook(KEY_RIGHT, &call_key_2, fractol_data());
	ftx_key_hook(KEY_UP, &call_key_2, fractol_data());
	ftx_key_hook(KEY_DOWN, &call_key_2, fractol_data());
	ftx_key_hook(KEY_PAD_0, &call_key_0, fractol_data());
	ftx_key_hook(KEY_PAD_PLUS, &call_key_1, fractol_data());
	ftx_key_hook(KEY_PAD_MINUS, &call_key_1, fractol_data());
	ftx_key_hook(KEY_H, &call_key_1, fractol_data());
	ftx_hook_mice_move(win, &call_mice_move, ftx_data());
	ftx_hook_mice_button(win, MICE_LEFT, &call_mice_button, win);
	ftx_hook_mice_button(win, MICE_SCROLL_DOWN, &call_mice_button, win);
	ftx_hook_mice_button(win, MICE_SCROLL_UP, &call_mice_button, win);
	first_args();
	ftx_start();
}
