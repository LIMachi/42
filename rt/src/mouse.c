/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 19:03:16 by hmartzol          #+#    #+#             */
/*   Updated: 2017/03/08 04:14:15 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_mouse		*mouse(void)
{
	static t_mouse mouse = (t_mouse){.is_select = 0, .x = 0, .y = 0};

	return (&mouse);
}

int			mouse_click(int key, int x, int y, void *data)
{
	int check;

	(void)data;
	if (!(x >= 0 && y >= 0 && x < prim_map()->size.x && y < prim_map()->size.y))
		return (0);
	check = prim_map()->data[prim_map()->size.x * y + x];
	if (check > 0 && key == 4)
		prim()[0][check - 1].radius *= 1.04f;
	if (check > 0 && key == 5)
		prim()[0][check - 1].radius /= 1.04f;
	if (key == 1)
		mouse()->is_select = check;
	ftocl_clear_current_kernel_arg(3);
	ftocl_set_current_kernel_arg(CL_MEM_READ_ONLY, 3, sizeof(t_primitive) *
		argn()->nb_objects, (void*)*prim());
	update(1);
	return (0);
}

int			mouse_off(int key, int x, int y, void *data)
{
	(void)x;
	(void)y;
	(void)data;
	if (key == 1)
		mouse()->is_select = 0;
	return (0);
}

void		new_pos(cl_float4 *item_pos, int x, int y)
{
	*item_pos = cl_float4_add(cam()->pos, ft_vector_thales(cam()->pos,
	cl_float4_add(cl_float4_add(cl_float4_scale(cam()->right,
	(cl_float)(mouse()->x - argn()->screen_size.x / 2)),
	cl_float4_scale(cam()->up,
	-(cl_float)(mouse()->y - argn()->screen_size.y / 2))),
	cl_float4_scale(cam()->dir, cam()->dist)),
	cl_float4_sub(*item_pos, cam()->pos), cl_float4_add(cl_float4_add(
	cl_float4_scale(cam()->right, (cl_float)(x - argn()->screen_size.x / 2)),
	cl_float4_scale(cam()->up, -(cl_float)(y - argn()->screen_size.y / 2))),
	cl_float4_scale(cam()->dir, cam()->dist))));
}

int			mouse_move(int x, int y, void *data)
{
	static int upd = 0;

	if (!mouse()->is_select)
		return (0);
	ft_void(upd++ && data);
	if (upd != UPD || (upd = 0))
		return (0);
	if (mouse()->is_select > 0)
	{
		new_pos(&prim()[0][mouse()->is_select - 1].position, x, y);
		ftocl_clear_current_kernel_arg(3);
		ftocl_set_current_kernel_arg(CL_MEM_READ_ONLY, 3, sizeof(t_primitive) *
		argn()->nb_objects, (void*)*prim());
	}
	else
	{
		new_pos(&lights()[0][-mouse()->is_select - 1].position, x, y);
		ftocl_clear_current_kernel_arg(4);
		ftocl_set_current_kernel_arg(CL_MEM_READ_ONLY, 4, sizeof(t_light) *
			argn()->nb_lights, (void*)*lights());
	}
	mouse()->x = x;
	mouse()->y = y;
	update(1);
	return (0);
}
