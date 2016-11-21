/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 02:04:31 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/21 04:27:19 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <libftocl.h>

typedef struct	s_fractol_args
{
	cl_uint		iterations;
	t_cl_comp	z0;
	t_cl_point	size;
	t_cl_comp	vp_ul;
	t_cl_comp	vp_dr;
	cl_uint		anti_alias;
}				t_fractol_args;

typedef struct	s_fractol_data
{
	t_fractol_args	args;
	size_t			array_size;
	cl_int			*rbmp;
	int				lock;
	int				info;
}				t_fractol_data;

#endif
