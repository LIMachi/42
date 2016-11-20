/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftocl_set_current_kernel.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 11:15:26 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/19 16:09:19 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftocl.h>

/*
** will search (in the current program) and set the current kernel to the kernel
** correcponding to the kernel_id passed in arg, will return 0 on succes, 1 if
** there was no correcponding kernel to the kernel_id and -1 if an error occured
*/

int	ftocl_set_current_kernel(uint64_t kernel_id)
{
	t_ocl_data	*data;
	t_2list		*list;

	data = ftocl_data();
	if (data->current_program == NULL || data->current_kernel == NULL ||
		data->current_program->kernels == NULL)
		return (-1);
	if (data->current_kernel->id == kernel_id)
		return (0);
	list = data->current_program->kernels;
	while (((t_ocl_kernel*)list->data)->id != kernel_id && list->next != NULL)
		list = list->next;
	if (((t_ocl_kernel*)list->data)->id == kernel_id)
	{
		data->current_kernel = (t_ocl_kernel*)list->data;
		return (0);
	}
	return (1);
}
