/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftocl.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 09:53:54 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/14 11:44:28 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#if OS == LINUX
# include <CL/opencl.h>
#elif OS == MACINTOCH
# include <OpenCL/opencl.h>
#else
# error "unsuported os"
#endif

#define FTOCL_ALL_ARGS ((cl_uint)-1)

#include <stdio.h>
//#define DEBUG printf("function: %s, line %d, potential error: %d\n", __func__, __LINE__, 0/*(int)err*/);
#define DEBUG ft_putstr("function: "); ft_putstr(__func__); ft_putstr(", line: "); ft_putnbr(__LINE__); ft_putchar('\n');

//note: the id of a kernel is the first 8 ascii characters of his name (faster search and more intuitive)
//note: the id must be filled with 8 ascii, and all unused ascii must be \0

typedef struct		s_ocl_kernel
{
	uint64_t		id;
	cl_kernel		kernel;
	cl_uint			nb_args;
	cl_mem			*args;
	size_t			*sizes;
}					t_ocl_kernel;

//note: the id of a program is an user given 8 ascii characters stored as uint64_t (faster search and more intuitive)
//note: the id must be filled with 8 ascii, and all unused ascii must be \0

typedef struct		s_ocl_program
{
	uint64_t		id;
	const char		*source;
	cl_program		program;
	t_2list			*kernels;
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
cl_int				ftocl_make_program(uint64_t *id, const char *src);
void				ftocl_end(void);
void				ftocl_clear_current_kernel_arg(cl_uint index);
void				ftocl_read_current_kernel_arg(cl_uint index, void *ptr);
int					ftocl_set_current_kernel_arg(cl_mem_flags flags,
										cl_uint index, size_t size, void *ptr);
int					ftocl_set_current_kernel(uint64_t *kernel_id);
int					ftocl_set_current_program(uint64_t *program_id);
void				ftocl_start_current_kernel(cl_uint work_dim,
				const size_t *global_work_size, const size_t *local_work_size);
