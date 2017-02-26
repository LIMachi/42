/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftocl_set_current_kernel_arg.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 11:16:03 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/25 23:46:37 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftocl.h>

/*
** will create a buffer for the arg "index", eventually making a copy of the
** content of ptr (if it is not NULL), and set the kernel arg "index" to the
** new buffer
*/

/*
** do not call this function if the kernel is already or still set (will return
** an error)
*/

int	ftocl_set_current_kernel_arg(cl_mem_flags flags, cl_uint index,
											size_t size, void *ptr)
{
	t_ocl_data	*data;
	cl_int		err;

	data = ftocl_data();
	if (data->current_kernel == NULL || index >= data->current_kernel->nb_args
		|| data->current_kernel->args[index] != 0)
	{
		ft_error(EINTERN, "kernel arg can't be created or is already set\n");
		return (-1);
	}
	if (ptr != NULL)
		flags |= CL_MEM_COPY_HOST_PTR;
	data->current_kernel->args[index] = clCreateBuffer(data->context, flags,
														size, ptr, &err);
	data->current_kernel->sizes[index] = size;
	if (err != CL_SUCCESS)
	{
		//ft_printf("error: %d\n", err == CL_OUT_OF_HOST_MEMORY);
		ft_error(EINTERN, "buffer creation failed\n");
	}
	err = clSetKernelArg(data->current_kernel->kernel, index, sizeof(cl_mem),
								(void *)&data->current_kernel->args[index]);
	if (err != CL_SUCCESS)
		ft_error(EINTERN, "setting of kernel arg failed\n");
	return (0);
}
