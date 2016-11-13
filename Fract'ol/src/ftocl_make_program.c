/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftocl_make_program.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 02:02:20 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/13 09:14:58 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftocl.h>

static t_ocl_kernel	*sf_parse_and_create_kernel(t_ocl_data *data,
												char *kernel_start)
{
	char	*kernel_end;
	t_ocl_kernel	*out;
	cl_int			e;
	char	name_buff[128];

	kernel_start += 8;
	while (ft_isspace(*kernel_start))
		++kernel_start;
	while (ft_isalnum(*kernel_start))
		++kernel_start;
	while (ft_isspace(*kernel_start))
		++kernel_start;
	out = (t_ocl_kernel*)ft_malloc(sizeof(t_ocl_kernel));
	*out = (t_ocl_kernel){.id = *(uint64_t*)kernel_start, .kernel = 0,
						.nb_args = 1, .args = NULL, .sizes = NULL};
	e = 0;
	while (ft_isunix(*kernel_start))
		name_buff[e++] = *kernel_start++;
	name_buff[e] = 0;
	kernel_start = ft_strchr(kernel_start, '(');
	kernel_end = ft_strchr(kernel_start, ')');
	while (((kernel_start = ft_strchr(kernel_start + 1, ',')) != NULL)
			&& (unsigned long)kernel_start < (unsigned long)kernel_end)
		++out->nb_args;
	out->args = (cl_mem*)ft_memalloc(sizeof(cl_mem) * out->nb_args);
	out->sizes = (size_t*)ft_memalloc(sizeof(size_t) * out->nb_args);
	out->kernel = clCreateKernel(data->current_program->program, name_buff, &e);
	return (out);
}

cl_int				ftocl_make_program(uint64_t *id, const char *src)
{
	cl_int			err;
	t_ocl_data		*data;
	t_ocl_program	*program;
	char			*ptr;
	t_ocl_kernel	*kernel;

	data = ftocl_data();
	program = (t_ocl_program*)ft_malloc(sizeof(t_ocl_program));
	*program = (t_ocl_program){.id = *id, .source = src, .program = 0,
								.kernels = NULL};
	program->program = clCreateProgramWithSource(data->context, 1,
									(const char **)&src, 0, &err);
	err = clBuildProgram(program->program, 0, NULL, NULL, NULL, NULL);
	(void)ft_2l_add_node(&data->programs, ft_2l_new_node((void*)program));
	data->current_program = program;
	ptr = (char*)src - 1;
	while ((ptr = ft_strstr(ptr + 1, "__kernel")) != NULL)
	{
		kernel = sf_parse_and_create_kernel(data, ptr);
		if (data->current_kernel == NULL)
			data->current_kernel = kernel;
		(void)ft_2l_add_node(&data->current_program->kernels,
							ft_2l_new_node((void*)kernel));
	}
	if (data->current_kernel == NULL)
		ft_error(EINTERN, "No kernel was founs in program sources\n");
	return (err);
}