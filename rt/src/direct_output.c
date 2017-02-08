/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direct_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 12:13:23 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/30 15:21:28 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_output(void)
{
	out()->size.x = argn()->screen_size.x;
	out()->size.y = argn()->screen_size.y;
	prim_map()->size.x = argn()->screen_size.x;
	prim_map()->size.y = argn()->screen_size.y;
	if ((out()->data = (int*)ft_memalloc(sizeof(int)
		* out()->size.x * out()->size.y)) == NULL ||
		(prim_map()->data = (int*)ft_memalloc(sizeof(int)
		* prim_map()->size.x * prim_map()->size.y)) == NULL)
	{
		ft_error(ENOMEM, "Couldn't allocate GPU's output memory handler\n");
		ft_end(0);
	}
}

void	direct_output(char *path)
{
	size_t		size;
	t_bitmap	*bmp;

	out()->size.x = argn()->screen_size.x;
	out()->size.y = argn()->screen_size.y;
	if ((out()->data = (int*)ft_memalloc(sizeof(int)
		* out()->size.x * out()->size.y)) == NULL)
	{
		ft_error(ENOMEM, "Couldn't allocate GPU's output memory handler\n");
		ft_end(0);
	}
	size = 0;
	ftocl_set_current_kernel_arg(CL_MEM_READ_ONLY, 9, sizeof(cl_int), &size);
	size = out()->size.x * out()->size.y;
	ftocl_start_current_kernel(1, &size, NULL);
	ftocl_read_current_kernel_arg(0, out()->data);
	if ((bmp = ft_ubmp_to_bmp(out())) == NULL)
	{
		ft_error(ENOMEM, "Couldn't allocate bmp structure\n");
		ft_end(0);
	}
	ft_bitmap_file_save(path, bmp);
	ft_end(0);
}
