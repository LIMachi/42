/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftocl_read_current_kernel_arg.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 11:26:57 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/14 11:28:38 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftocl.h>

/*
** will copy the content of arg "index" of current kernel in ptr (ptr must
** have been allocated with sufficient space)
*/

void	ftocl_read_current_kernel_arg(cl_uint index, void *ptr)
{
	t_ocl_data	*data;
	cl_int		err;

	data = ftocl_data();
	err = clEnqueueReadBuffer(data->queue, data->current_kernel->args[index],
			CL_TRUE, 0, data->current_kernel->sizes[index], ptr, 0, 0, 0);
	if (err != CL_SUCCESS)
		ft_error(EINTERN, "reading of kernel arg failed\n");
}
