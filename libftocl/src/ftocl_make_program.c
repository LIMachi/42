/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftocl_make_program.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 02:02:20 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/04 18:54:59 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftocl.h>

static inline char			*sf_the_thing(char *kernel_start)
{
	kernel_start += 8;
	while (ft_isspace(*kernel_start))
		++kernel_start;
	while (ft_isalnum(*kernel_start))
		++kernel_start;
	while (ft_isspace(*kernel_start))
		++kernel_start;
	return (kernel_start);
}

static inline t_ocl_kernel	*sf_parse_and_create_kernel(t_ocl_data *data,
												char *kernel_start)
{
	char			*kernel_end;
	t_ocl_kernel	*out;
	cl_int			e;
	char			name_buff[128];

	kernel_start = sf_the_thing(kernel_start);
	out = (t_ocl_kernel*)ft_malloc(sizeof(t_ocl_kernel));
	e = 0;
	while (ft_isunix(*kernel_start))
		name_buff[e++] = *kernel_start++;
	name_buff[e] = 0;
	*out = (t_ocl_kernel){.id = 0, .kernel = 0,
						.nb_args = 1, .args = NULL, .sizes = NULL};
	out->id = ft_str_to_id64(name_buff);
	kernel_start = ft_strchr(kernel_start, '(');
	kernel_end = ft_strchr(kernel_start, ')');
	while (((kernel_start = ft_strchr(kernel_start + 1, ',')) != NULL)
			&& (unsigned long)kernel_start < (unsigned long)kernel_end)
		++out->nb_args;
	out->args = (cl_mem*)ft_memalloc(sizeof(cl_mem) * out->nb_args);
	out->sizes = (size_t*)ft_memalloc(sizeof(size_t) * out->nb_args);
	out->kernel = clCreateKernel(data->current_program->program, name_buff, &e);
	if (e != CL_SUCCESS)
		ft_error(EINTERN, "Kernel creation failed\n");
	return (out);
}

static inline void			sf_return_of_the_random_name(t_ocl_data *data,
														char *ptr)
{
	t_ocl_kernel	*kernel;
	void			*tmp;

	kernel = sf_parse_and_create_kernel(data, ptr);
	if (data->current_kernel == NULL)
		data->current_kernel = kernel;
	(void)ft_2lstadd(&data->current_program->kernels,
						tmp = ft_2lstnew(0, (void*)kernel, 0));
}

cl_int						ftocl_make_program(uint64_t id, const char *src,
												const char *opt)
{
	cl_int			err;
	t_ocl_data		*data;
	t_ocl_program	*program;
	char			*ptr;

	if (src == NULL)
		return (CL_INVALID_VALUE);
	data = ftocl_data();
	program = (t_ocl_program*)ft_malloc(sizeof(t_ocl_program));
	*program = (t_ocl_program){.id = id, .source = src, .program = 0,
								.kernels = NULL};
	program->program = clCreateProgramWithSource(data->context, 1,
									(const char **)&src, 0, &err);
	if (err != CL_SUCCESS)
		ft_error(EINTERN, "Could not create program with sources\n");
	if ((err = clBuildProgram(program->program, 0, 0, opt, 0, 0)) != CL_SUCCESS)
		ft_error(EINTERN, "Could not build program\n");
	(void)ft_2lstadd(&data->programs, ft_2lstnew(0, (void*)program, 0));
	data->current_program = program;
	ptr = (char*)src - 1;
	while ((ptr = ft_strstr(ptr + 1, "__kernel")) != NULL)
		sf_return_of_the_random_name(data, ptr);
	if (data->current_kernel == NULL)
		ft_log("Warning: No kernel was founs in program sources\n");
	return (err);
}
