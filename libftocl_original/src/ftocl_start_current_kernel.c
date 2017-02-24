/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftocl_start_current_kernel.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 11:20:59 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/14 11:24:07 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftocl.h>

/*
** will trigger currently selected kernel (note, this function do not check
** if args of the kernel have been set and will throw an error description in
** log if an OpenCL error occures)
*/

/*
** this function is non block, the kernel might be still running when this
** function return
*/

void	ftocl_start_current_kernel(cl_uint work_dim,
				const size_t *global_work_size, const size_t *local_work_size)
{
	t_ocl_data	*data;
	cl_int		err;

	data = ftocl_data();
	err = clEnqueueNDRangeKernel(data->queue, data->current_kernel->kernel,
					work_dim, 0, global_work_size, local_work_size, 0, 0, 0);
	if (err != CL_SUCCESS)
		ft_error(EINTERN, "starting of kernel failed\n");
}
