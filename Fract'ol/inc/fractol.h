/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 02:04:31 by hmartzol          #+#    #+#             */
/*   Updated: 2017/03/02 13:11:30 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <libftocl.h>

# if OS == MACINTOCH
#  define WIDTH		2560
#  define HEIGHT	1440
# else
#  define WIDTH		1920
#  define HEIGHT	1080
# endif

typedef struct	s_fractol_args
{
	cl_uint		iterations;
	t_cl_comp	z0;
	t_cl_point	size;
	t_cl_comp	vp_ul;
	t_cl_comp	vp_dr;
	cl_float	color;
}				t_fractol_args;

typedef struct	s_fractol_data
{
	t_fractol_args	args;
	size_t			array_size;
	cl_int			*rbmp;
	int				lock;
	int				info;
}				t_fractol_data;

void			fractol(void);
void			zoom(cl_float zoom);
void			view_port_cut(t_fractol_args *args, t_point a, t_point b);
t_fractol_data	*fractol_data(void);
int				refresh_fractol_window(t_window *win);
int				call_key_0(int key, int status, void *data);
int				call_key_1(int key, int status, void *data);
int				call_key_2(int key, int status, void *data);
int				call_mice_button(int button, int status, void *data);
int				call_mice_move(t_point pos, t_point click_pos, void *data);
void			print_info(t_fractol_data *data, t_image *img);

#endif
