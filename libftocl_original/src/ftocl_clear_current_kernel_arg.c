/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftocl_clear_current_kernel_arg.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 11:24:27 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/14 11:26:39 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftocl.h>

/*
** clear the arg "index" of the current kernel, the arg must be re-set after
** this function if you want to restart the kernel
*/

void	ftocl_clear_current_kernel_arg(cl_uint index)
{
	t_ocl_data	*data;

	data = ftocl_data();
	if (data->current_kernel == NULL || data->current_kernel->args == NULL ||
			(index >= data->current_kernel->nb_args && index != FTOCL_ALL_ARGS)
			|| data->current_kernel->sizes == NULL)
		ft_error(EINTERN, "can't clear current kernel arg\n");
	if (index != FTOCL_ALL_ARGS)
	{
		if (data->current_kernel->args[index])
			clReleaseMemObject(data->current_kernel->args[index]);
		data->current_kernel->args[index] = 0;
		data->current_kernel->sizes[index] = 0;
	}
	else
	{
		index = 0;
		while (index < data->current_kernel->nb_args)
		{
			if (data->current_kernel->args[index])
				clReleaseMemObject(data->current_kernel->args[index]);
			data->current_kernel->args[index] = 0;
			data->current_kernel->sizes[index++] = 0;
		}
	}
}
