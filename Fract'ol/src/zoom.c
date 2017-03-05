/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 16:55:04 by hmartzol          #+#    #+#             */
/*   Updated: 2017/03/02 13:15:22 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftocl.h>
#include <libftx.h>
#include <fractol.h>

static void	sf_view_port_cut(t_fractol_args *args, t_point a, t_point b)
{
	t_cl_comp	tmp_ul;
	t_cl_comp	tmp_dr;

	tmp_ul.r = args->vp_ul.r + (args->vp_dr.r - args->vp_ul.r) *
									((cl_float)a.x / (cl_float)args->size.x);
	tmp_dr.r = args->vp_ul.r + (args->vp_dr.r - args->vp_ul.r) *
									((cl_float)b.x / (cl_float)args->size.x);
	tmp_ul.i = args->vp_ul.i + (args->vp_dr.i - args->vp_ul.i) *
									((cl_float)a.y / (cl_float)args->size.y);
	tmp_dr.i = args->vp_ul.i + (args->vp_dr.i - args->vp_ul.i) *
									((cl_float)b.y / (cl_float)args->size.y);
	args->vp_ul = tmp_ul;
	args->vp_dr = tmp_dr;
}

void		view_port_cut(t_fractol_args *args, t_point a, t_point b)
{
	cl_float	r;
	t_point		t;

	if (ft_point_equal(a, b))
		return ;
	if (a.x > b.x)
		ft_swapi(&a.x, &b.x);
	if (a.y > b.y)
		ft_swapi(&a.y, &b.y);
	if (*ftx_key_status(KEY_R) != FTX_KEY_STATUS_PRESSED)
	{
		r = (cl_float)args->size.x / (cl_float)args->size.y;
		t = ft_point_difference(a, b);
		(void)(t.x < t.y * r ? (b.x = a.x + t.y * r) : 0);
		(void)(t.x > t.y * r ? (b.y = a.y + t.x / r) : 0);
	}
	sf_view_port_cut(args, a, b);
}

void		zoom(cl_float zoom)
{
	t_fractol_args	*args;
	t_point			mice;
	t_cl_comp		p;
	t_cl_comp		s;

	args = &fractol_data()->args;
	mice = ftx_data()->focused_window->mice.pos;
	p = (t_cl_comp){.r = (cl_float)mice.x / (cl_float)args->size.x,
					.i = (cl_float)mice.y / (cl_float)args->size.y};
	s = (t_cl_comp){.r = args->vp_dr.r - args->vp_ul.r,
					.i = args->vp_dr.i - args->vp_ul.i};
	s = (t_cl_comp){.r = s.r * zoom - s.r, .i = s.i * zoom - s.i};
	args->vp_dr.r -= (1.0 - p.r) * s.r;
	args->vp_ul.r += p.r * s.r;
	args->vp_dr.i -= (1.0 - p.i) * s.i;
	args->vp_ul.i += p.i * s.i;
}
