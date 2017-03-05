/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_mice.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 18:00:30 by hmartzol          #+#    #+#             */
/*   Updated: 2017/03/02 13:13:09 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftocl.h>
#include <libftx.h>
#include <fractol.h>

t_cl_comp	mice_to_comp(t_point mice)
{
	t_fractol_args	*args;
	t_cl_comp		p;
	t_cl_comp		s;

	args = &fractol_data()->args;
	p = (t_cl_comp){.r = (cl_float)mice.x / (cl_float)args->size.x,
					.i = (cl_float)mice.y / (cl_float)args->size.y};
	s = (t_cl_comp){.r = args->vp_dr.r - args->vp_ul.r,
					.i = args->vp_dr.i - args->vp_ul.i};
	return ((t_cl_comp){
		.r = args->vp_ul.r + s.r * p.r,
		.i = args->vp_ul.i + s.i * p.i});
}

int			call_mice_move(t_point pos, t_point click_pos, void *data)
{
	t_window	*win;
	int			up;

	(void)click_pos;
	win = ((t_ftx_data*)data)->focused_window;
	up = 0;
	if (*ftx_button_status(MICE_LEFT) == FTX_KEY_STATUS_PRESSED)
		up = 1;
	if (fractol_data()->lock == 0 && (up = 1))
	{
		fractol_data()->args.z0 = mice_to_comp(pos);
		ftocl_clear_current_kernel_arg(0);
		ftocl_set_current_kernel_arg(CL_MEM_READ_ONLY, 0,
						sizeof(t_fractol_args), &fractol_data()->args);
	}
	if (up)
		refresh_fractol_window(win);
	return (0);
}

int			call_mice_button(int button, int status, void *data)
{
	int				up;
	t_fractol_data	*f;
	t_window		*win;

	up = 0;
	f = fractol_data();
	win = (t_window*)data;
	if (button == MICE_SCROLL_UP && status == FTX_KEY_STATUS_PRESSED
			&& (up = 1))
		zoom(1.1);
	if (button == MICE_SCROLL_DOWN && status == FTX_KEY_STATUS_PRESSED
			&& (up = 1))
		zoom(1.0 / 1.1);
	if (button == MICE_LEFT && status == FTX_KEY_STATUS_RELEASED && (up = 1))
		view_port_cut(&f->args, win->mice.click_pos, win->mice.pos);
	if (up)
	{
		ftocl_clear_current_kernel_arg(0);
		ftocl_set_current_kernel_arg(CL_MEM_READ_ONLY, 0,
									sizeof(t_fractol_args), &f->args);
		refresh_fractol_window(ftx_data()->focused_window);
	}
	return (0);
}
