/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 02:04:31 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/13 10:39:24 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

typedef struct	s_fractol_args
{
	cl_uint		iterations;
	cl_float	z0r;
	cl_float	z0i;
	cl_uint		width;
	cl_uint		length;
	cl_float	view_port_left;
	cl_float	view_port_up;
	cl_float	view_port_right;
	cl_float	view_port_down;
}				t_fractol_args;

typedef struct	s_fractol_data
{
	t_fractol_args	args;
	size_t			array_size;
	cl_int			*rbmp;
}				t_fractol_data;

#endif
