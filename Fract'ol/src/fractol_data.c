/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 17:25:16 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/21 18:15:05 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <libftx.h>
#include <fractol.h>

t_fractol_data	*fractol_data(void)
{
	static t_fractol_data	data = {.args = {.iterations = 750u,

	.z0 = (t_cl_comp){0.0, 0.0}, .size = (t_cl_point){WIDTH, HEIGHT},
	.vp_ul = (t_cl_comp){-1.77, -1.0}, .vp_dr = (t_cl_comp){1.77, 1.0},
	.color = 0}, .array_size = sizeof(cl_int) * WIDTH * HEIGHT,
	.rbmp = NULL, .lock = 1, .info = 1};
	if (data.rbmp == NULL)
		data.rbmp = (cl_int*)ft_memalloc(data.array_size);
	return (&data);
}
