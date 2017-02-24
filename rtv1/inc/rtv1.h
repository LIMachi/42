/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 00:05:50 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/15 00:52:38 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <libft.h>
# include <libftx.h>
# include <libftocl.h>

# define OCL_SOURCE_PATH "./scl/test.cl"

typedef struct	s_camera
{
	t_vector		pos;
	t_vector		dir;
	t_vector		up;
	t_vector		right;
	double			dist;
	t_quaternion	orientation;
}				t_camera;

typedef struct	s_primitive
{
	cl_int		type;
	cl_int		id;
	cl_float4	position;
	cl_float4	direction;
	cl_float	radius;
	cl_int		color;
}				t_primitive;

typedef struct	s_argn
{
	cl_int2		screen_size;
	cl_int		nb_objects;
}				t_argn;

#endif
