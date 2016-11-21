/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 17:44:01 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/21 20:47:07 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftocl.h>
#include <libftx.h>
#include <fractol.h>

int	call_key_0(int key, int status, void *data)
{
	int 		up;
	t_window	*win;

	win = (t_window*)data;
	up = 0;
	if (key == KEY_R && status == FTX_KEY_STATUS_PRESSED)
		up = 1;
	if (key == KEY_B && status == FTX_KEY_STATUS_PRESSED && (up = 1))
		ftx_fill_image(win->vbuffer, 0, 0.01);
	if (key == KEY_W && status == FTX_KEY_STATUS_PRESSED && (up = 1))
		ftx_fill_image(win->vbuffer, 0xFFFFFF, 0.01);
	if (key == KEY_S && status == FTX_KEY_STATUS_PRESSED &&
			*ftx_key_status(KEY_CTRL_LEFT) == FTX_KEY_STATUS_PRESSED)
		ftx_screenshoot(win, "./");
	if (key == KEY_L && status == FTX_KEY_STATUS_PRESSED)
		fractol_data()->lock = 1 - fractol_data()->lock;
	if (up)
		refresh_fractol_window(win);
	return (0);
}

static int	sf_call_key(int up, t_fractol_data *f)
{
	if (up == 0)
		return (0);
	ftocl_clear_current_kernel_arg(0);
	ftocl_set_current_kernel_arg(CL_MEM_READ_ONLY, 0,
								sizeof(t_fractol_args), &f->args);
	refresh_fractol_window(ftx_data()->focused_window);
	return (0);
}

int	call_key_2(int key, int status, void *data)
{
	int				up;
	t_fractol_data	*f;
	double			c;

	c = 0.0;
	if (!(up = 0) && status != FTX_KEY_STATUS_PRESSED)
		return (0);
	f = (t_fractol_data*)data;
	if ((key == KEY_LEFT || *ftx_key_status(KEY_LEFT)) && (up |= 1))
		c = -(f->args.vp_dr.r - f->args.vp_ul.r) / 30.0f;
	if ((key == KEY_RIGHT || *ftx_key_status(KEY_RIGHT)) && (up |= 1))
		c = (f->args.vp_dr.r - f->args.vp_ul.r) / 30.0f;
	if (up & 1)
		(void)((f->args.vp_dr.r += c) +
			(f->args.vp_ul.r += c));
	if ((key == KEY_UP || *ftx_key_status(KEY_UP)) && (up |= 2))
		c = -(f->args.vp_dr.i - f->args.vp_ul.i) / 30.0f;
	if ((key == KEY_DOWN || *ftx_key_status(KEY_DOWN)) && (up |= 2))
		c = (f->args.vp_dr.i - f->args.vp_ul.i) / 30.0f;
	if (up & 2)
		(void)((f->args.vp_dr.i += c) +
			(f->args.vp_ul.i += c));
	return (sf_call_key(up, f));
}

int	call_key_1(int key, int status, void *data)
{
	int				up;
	t_fractol_data	*f;

	if (!(up = 0) && status != FTX_KEY_STATUS_PRESSED)
		return (0);
	f = (t_fractol_data*)data;
	if (key == KEY_PAD_0 && (up = 1))
		*f = (t_fractol_data){(t_fractol_args){.iterations = 750u,
		.z0 = (t_cl_comp){0.0f, 0.0f}, .size = (t_cl_point){WIDTH, HEIGHT},
		.vp_ul = (t_cl_comp){-1.77f, -1.0f}, .vp_dr = (t_cl_comp){1.77f, 1.0f},
		.color = 0.0f}, .array_size = f->array_size, .rbmp = f->rbmp, .lock = 1,
		.info = 1};
	if (*ftx_key_status(KEY_I) && key == KEY_PAD_PLUS && (up = 1))
		f->args.iterations = (f->args.iterations += 1 + 9 * (f->args.iterations
	> 50) + 90 * (f->args.iterations > 500) < 5000) ? f->args.iterations : 5000;
	if (*ftx_key_status(KEY_I) && key == KEY_PAD_MINUS && (up = 1))
		f->args.iterations = (f->args.iterations -= 1 + 9 * (f->args.iterations
		> 50) + 90 * (f->args.iterations > 500) > 0) ? f->args.iterations : 1;
	if (*ftx_key_status(KEY_C) && (key == KEY_PAD_MINUS || key == KEY_PAD_PLUS)
			&& (up = 1))
		f->args.color += (cl_float)((key == KEY_PAD_PLUS) - (key == KEY_PAD_MINUS));
	if (key == KEY_H && (up = 1))
		f->info = 1 - f->info;
	return (sf_call_key(up, f));
}
