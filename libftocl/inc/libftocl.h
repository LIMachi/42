/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftocl.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 09:53:54 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/29 21:55:09 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTOCL_H
# define LIBFTOCL_H

# include <libft.h>

# if OS == LINUX
#  include <CL/opencl.h>
# elif OS == MACINTOCH
#  include <OpenCL/opencl.h>
# else
#  error "unsuported os"
# endif

# define FTOCL_ALL_ARGS ((cl_uint)-1)

typedef struct		s_cl_comp
{
	cl_float	r;
	cl_float	i;
}					t_cl_comp;

typedef struct		s_cl_point
{
	cl_int	x;
	cl_int	y;
}					t_cl_point;

/*
** note: the id of a kernel is the first 8 ascii characters of his name (faster
** search and more intuitive)
** note: the id must be filled with 8 ascii, and all unused ascii must be \0
*/

typedef struct		s_ocl_kernel
{
	uint64_t	id;
	cl_kernel	kernel;
	cl_uint		nb_args;
	cl_mem		*args;
	size_t		*sizes;
}					t_ocl_kernel;

/*
** note: the id of a program is an user given 8 ascii characters stored as
** uint64_t (faster search and more intuitive)
** note: the id must be filled with 8 ascii, and all unused ascii must be \0
*/

typedef struct		s_ocl_program
{
	uint64_t	id;
	const char	*source;
	cl_program	program;
	t_2list		*kernels;
}					t_ocl_program;

typedef struct		s_ocl_data
{
	cl_platform_id		platform;
	cl_device_id		device;
	cl_context			context;
	cl_command_queue	queue;
	t_2list				*programs;
	t_ocl_program		*current_program;
	t_ocl_kernel		*current_kernel;
}					t_ocl_data;

t_ocl_data			*ftocl_data(void);
cl_int				ftocl_make_program(uint64_t id, const char *src,
												const char *opt);
void				ftocl_end(void);
void				ftocl_clear_current_kernel_arg(cl_uint index);
void				ftocl_read_current_kernel_arg(cl_uint index, void *ptr);
int					ftocl_set_current_kernel_arg(cl_mem_flags flags,
										cl_uint index, size_t size, void *ptr);
int					ftocl_set_current_kernel(uint64_t kernel_id);
int					ftocl_set_current_program(uint64_t program_id);
void				ftocl_start_current_kernel(cl_uint work_dim,
				const size_t *global_work_size, const size_t *local_work_size);
cl_int				ftocl_run_percent_callback(const size_t global_work_size,
		int arg_index, void (*callback)(int percent, void *data), void *data);
#endif
