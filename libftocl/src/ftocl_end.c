/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftocl_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 09:22:52 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/27 16:53:15 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftocl.h>

static inline void			sf_free(void *ptr)
{
	if (ptr != NULL)
		(void)ft_free(ptr);
}

static inline t_ocl_data	*sf_end(t_ocl_data *data)
{
	t_2list		*list;
	cl_uint		i;

	while (data->programs != NULL)
	{
		while ((list = ((t_ocl_program*)data->programs->data)->kernels) != NULL)
		{
			i = 0;
			while (i < ((t_ocl_kernel*)list->data)->nb_args)
				if (((t_ocl_kernel*)list->data)->args[i++])
					clReleaseMemObject(((t_ocl_kernel*)list->data)->args[i
																		- 1]);
			sf_free(((t_ocl_kernel*)list->data)->args);
			sf_free(((t_ocl_kernel*)list->data)->sizes);
			if (((t_ocl_kernel*)list->data)->kernel)
				clReleaseKernel(((t_ocl_kernel*)list->data)->kernel);
			((t_ocl_program*)data->programs->data)->kernels = list->next;
			sf_free(list);
		}
		if (((t_ocl_program*)data->programs->data)->program)
			clReleaseProgram(((t_ocl_program*)data->programs->data)->program);
		sf_free((void *)((t_ocl_program*)data->programs->data)->source);
		data->programs = data->programs->next;
	}
	return (data);
}

void						ftocl_end(void)
{
	t_ocl_data	*data;

	data = sf_end(ftocl_data());
	if (data->queue)
		clReleaseCommandQueue(data->queue);
	if (data->context)
		clReleaseContext(data->context);
	ft_bzero(data, sizeof(t_ocl_data));
}
