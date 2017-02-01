/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftocl_start_current_kernel.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 11:20:59 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/29 21:52:48 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftocl.h>

/*
** will trigger currently selected kernel (note, this function do not check
** if args of the kernel have been set and will throw an error description in
** log if an OpenCL error occures)
*/

/*
** global_work_size must be dividable by local_work_size, if local_work_size is
** NULL, OpenCL will figure wich local_work_size is the best.
*/

void			ftocl_start_current_kernel(cl_uint work_dim,
				const size_t *global_work_size, const size_t *local_work_size)
{
	t_ocl_data	*data;
	cl_int		err;
	cl_event	event;

	data = ftocl_data();
	err = clEnqueueNDRangeKernel(data->queue, data->current_kernel->kernel,
			work_dim, NULL, global_work_size, local_work_size, 0, NULL, &event);
	clWaitForEvents(1, &event);
	clReleaseEvent(event);
	if (err != CL_SUCCESS)
		ft_error(EINTERN, "starting of kernel failed\n");
}
