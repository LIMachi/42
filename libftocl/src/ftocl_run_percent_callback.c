/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftocl_run_percent_callback.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 19:09:18 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/29 22:04:48 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftocl.h>

/*
** will execute 100 ftocl_start_current_kernel changing the value of the kernel
** argument indexed by arg_index to the current number of the kernel, and
** calling the function callback with the number of the kernel and the data
** passed in last arg.
** this function assume a work dim of 1 and a local_work_size of NULL
** this function will call 101 times the callback (0 and 100 inclusive)
** return an error code if a clEnqueueNDRangeKernel fails
*/

cl_int	ftocl_run_percent_callback(const size_t global_work_size, int arg_index,
						void (*callback)(int percent, void *data), void *data)
{
	int			current;
	cl_int		err;
	size_t		work_size;
	cl_int		shift;

	current = 0;
	callback(current, data);
	work_size = global_work_size / 100;
	while (++current <= 100)
	{
		shift = work_size * (current - 1);
		if (current == 100 && global_work_size % 100)
			work_size += global_work_size % 100;
		ftocl_set_current_kernel_arg(CL_MEM_READ_ONLY, arg_index,
									sizeof(cl_int), &shift);
		if ((err = clEnqueueNDRangeKernel(ftocl_data()->queue,
				ftocl_data()->current_kernel->kernel, 1, NULL, &work_size, NULL,
				0, NULL, NULL)) != CL_SUCCESS)
			break ;
		callback(current, data);
		ftocl_clear_current_kernel_arg(arg_index);
	}
	if (err != CL_SUCCESS)
		ftocl_clear_current_kernel_arg(arg_index);
	return (err);
}
