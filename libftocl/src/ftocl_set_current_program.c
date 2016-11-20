/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftocl_set_current_program.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 11:14:26 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/19 16:09:34 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftocl.h>

/*
** will search and set the current program to the program correcponding to the
** program_id passed in arg, will return 0 on succes, 1 if there was no
** correcponding program to the program_id and -1 if an error occured
*/

int		ftocl_set_current_program(uint64_t program_id)
{
	t_ocl_data	*data;
	t_2list		*list;

	data = ftocl_data();
	if (data->current_program == NULL || data->programs == NULL)
		return (-1);
	if (data->current_program->id == program_id)
		return (0);
	list = data->programs;
	while (((t_ocl_program*)list->data)->id != program_id && list->next != NULL)
		list = list->next;
	if (((t_ocl_program*)list->data)->id == program_id)
	{
		data->current_program = (t_ocl_program*)list->data;
		return (0);
	}
	return (1);
}
