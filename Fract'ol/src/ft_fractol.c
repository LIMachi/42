#include <stdio.h>
#include <libft.h>
#include <libftx.h>
#include <libftocl.h>
#include <fractol.h>

/*
** will search and set the current program to the program correcponding to the
** program_id passed in arg, will return 0 on succes and -1 on faillure
*/

int		ftocl_set_current_program(uint64_t *program_id)
{
	t_ocl_data	*data;
	t_2list		*list;

	data = ftocl_data();
	if (data->current_program == NULL || data->programs == NULL)
		return (-1);
	if (data->current_program->id == *program_id)
		return (0);
	list = data->programs;
	while (((t_ocl_program*)list->data)->id != *program_id && list->next != NULL)
		list = list->next;
	if (((t_ocl_program*)list->data)->id == *program_id)
	{
		data->current_program = (t_ocl_program*)list->data;
		return (0);
	}
	return (-1);
}

/*
** will search (in the current program) and set the current kernel to the kernel
** correcponding to the lernel_id passed in arg, will return 0 on succes and -1
** on faillure
*/

int	ftocl_set_current_kernel(uint64_t *kernel_id)
{
	t_ocl_data	*data;
	t_2list		*list;

	data = ftocl_data();
	if (data->current_program == NULL || data->current_kernel == NULL ||
		data->current_program->kernels == NULL)
		return (-1);
	if (data->current_kernel->id == *kernel_id)
		return (0);
	list = data->current_program->kernels;
	while (((t_ocl_kernel*)list->data)->id != *kernel_id && list->next != NULL)
		list = list->next;
	if (((t_ocl_kernel*)list->data)->id == *kernel_id)
	{
		data->current_kernel = (t_ocl_kernel*)list->data;
		return (0);
	}
	return (-1);
}

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
		ft_error(EINTERN, "buffer creation failed\n");
	err = clSetKernelArg(data->current_kernel->kernel, index, sizeof(cl_mem),
								(void *)&data->current_kernel->args[index]);
	if (err != CL_SUCCESS)
		ft_error(EINTERN, "setting of kernel arg failed\n");
	return (0);
}

void	ftocl_start_current_kernel(cl_uint work_dim,
				const size_t *global_work_size, const size_t *local_work_size)
{
	t_ocl_data	*data;
	cl_int		err;

	data = ftocl_data();
	err = clEnqueueNDRangeKernel(data->queue, data->current_kernel->kernel,
					work_dim, 0, global_work_size, local_work_size, 0, 0, 0);
	if (err != CL_SUCCESS)
		ft_error(EINTERN, "starting of kernel failed\n");
}

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

void	ftocl_read_current_kernel_arg(cl_uint index, void *ptr)
{
	t_ocl_data	*data;
	cl_int		err;

	data = ftocl_data();
	err = clEnqueueReadBuffer(data->queue, data->current_kernel->args[index],
			CL_TRUE, 0, data->current_kernel->sizes[index], ptr, 0, 0, 0);
	if (err != CL_SUCCESS)
		ft_error(EINTERN, "reading of kernel arg failed\n");
}

/*
int	main(int argc, char **argv)
{
	size_t	x_pix = 30;
	size_t	y_pix = 20;
	const size_t	mod = (x_pix * y_pix) % 16;
	const size_t	array_size = sizeof(cl_int) * ((x_pix * y_pix) + (mod ? 16 - mod : 0));
	char					*program_source = NULL;
	int						fd;
	cl_program program;
	cl_kernel kernel;
	cl_int		*hc = (cl_int*)ft_malloc(array_size);
	float hvpxl = -2.0f;
	float hvpyu = -2.0f;
	float hvpxr = 2.0f;
	float hvpyd = 2.0f;
	int		hl = 100;
	cl_mem dl, dvpxl, dvpxr, dvpyu, dvpyd, dxp, dyp, dc;

	if (argc < 2)
		return (0);
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return (-1);
	program_source = ft_readfile(fd);
	close(fd);
	ftocl_make_program((uint64_t*)"fractol ", program_source);
	ftocl_set_current_program((uint64_t*)"fractol ");
	ftocl_set_current_kernel((uint64_t*)"mandelbr");
	ftocl_set_current_kernel_arg(CL_MEM_READ_ONLY, 0, sizeof(cl_float), &hvpxl);
	ftocl_set_current_kernel_arg(CL_MEM_READ_ONLY, 1, sizeof(cl_float), &hvpyu);
	ftocl_set_current_kernel_arg(CL_MEM_READ_ONLY, 2, sizeof(cl_float), &hvpxr);
	ftocl_set_current_kernel_arg(CL_MEM_READ_ONLY, 3, sizeof(cl_float), &hvpyd);
	ftocl_set_current_kernel_arg(CL_MEM_READ_ONLY, 4, sizeof(cl_uint), &x_pix);
	ftocl_set_current_kernel_arg(CL_MEM_READ_ONLY, 5, sizeof(cl_uint), &y_pix);
	ftocl_set_current_kernel_arg(CL_MEM_READ_ONLY, 6, sizeof(cl_int), &hl);
	ftocl_set_current_kernel_arg(CL_MEM_WRITE_ONLY, 7, array_size, NULL);
	ftocl_start_current_kernel(1, &array_size, NULL);
	ftocl_read_current_kernel_arg(7, hc);
	for(int i = 0; i < y_pix; ++i)
	{
		for(int j = 0; j < x_pix; ++j)
			printf("0x%X ", hc[i * x_pix + j]);
		printf("\n");
	}
	ft_free(hc);
	ftocl_end();
}
*/

void	ft_fractol_data_init(t_fractol_data	*data)
{
	data->args.iterations = 100;
	data->args.z0r = 0;
	data->args.z0i = 0;
	data->args.width = 1920;
	data->args.length = 1080;
	data->args.view_port_left = -3.0f;
	data->args.view_port_right = 3.0f;
	data->args.view_port_up = -2.0f;
	data->args.view_port_down = 2.0f;
	data->array_size = sizeof(cl_int) * 2073600;
	data->rbmp = (cl_int*)ft_memalloc(data->array_size);
}

t_fractol_data	*ft_fractol_data(void)
{
	static t_fractol_data	data = {0};

	if (data.args.width == 0 && data.args.length == 0)
		ft_fractol_data_init(&data);
	return (&data);
}

int		fill_fractol(t_window *win, t_image *img)
{
	static t_fractol_data	*data = NULL;
	int						x;
	int						y;

	if (data == NULL)
		data = ft_fractol_data();
	ftocl_start_current_kernel(1, &data->array_size, NULL);
	ftocl_read_current_kernel_arg(1, data->rbmp);
	y = -1;
	while (++y < data->args.length && (x = -1))
		while (++x < data->args.width)
			ftx_putpixelimg(img, ft_point(x, y), data->rbmp[y * data->args.width + x]);
	img->update = 1;
	return (0);
}

int		fill_info(t_window *win, t_image *img)
{
//	t_fractol_data	*data;

	(void)win;
	(void)img;
//	data = (t_fractol_data*)win->data;
//	ftx_clear_img(img);
//	ftx_print_str(img, ft_point(1, 1), WHITE, buff);
//	sprintf(buff, "right: %f", data->args.view_port_right);
//	ftx_print_str(img, ft_point(1, 11), WHITE, buff);
//	sprintf(buff, "up: %f", data->args.view_port_up);
//	ftx_print_str(img, ft_point(1, 21), WHITE, buff);
//	sprintf(buff, "down: %f", data->args.view_port_down);
//	ftx_print_str(img, ft_point(1, 31), WHITE, buff);
//	img->update = 1;
	return (0);
}

int		update(void	*ptr)
{
	int						up;
	static t_fractol_data	*data = NULL;
	int						tmp;
	t_complex				c;

	up = 0;
	if (data == NULL)
		data = ft_fractol_data();
	if (ftx_is_button_press(KEY_I))
	{
		if (ftx_is_button_press(KEY_PAD_PLUS) && (up = 1))
			data->args.iterations += 1;
		if (ftx_is_button_press(KEY_PAD_MINUS) && (data->args.iterations > 2) && (up = 1))
			data->args.iterations -= 1;
	}
	if (ftx_is_button_press(KEY_Z))
	{
		if (ftx_is_button_press(KEY_PAD_PLUS) && (up = 1))
		{
			data->args.view_port_up /= 1.5;
			data->args.view_port_down /= 1.5;
			data->args.view_port_left /= 1.5;
			data->args.view_port_right /= 1.5;
		}
		if (ftx_is_button_press(KEY_PAD_MINUS) && (up = 1))
		{
			data->args.view_port_up *= 1.5;
			data->args.view_port_down *= 1.5;
			data->args.view_port_left *= 1.5;
			data->args.view_port_right *= 1.5;
		}
	}
	if (ftx_is_button_press(KEY_LEFT) && (up = 1))
	{
		c.r = (data->args.view_port_right - data->args.view_port_left) / 60;
		data->args.view_port_left -= c.r;
		data->args.view_port_right -= c.r;
	}
	if (ftx_is_button_press(KEY_RIGHT) && (up = 1))
	{
		c.r = (data->args.view_port_right - data->args.view_port_left) / 60;
		data->args.view_port_left += c.r;
		data->args.view_port_right += c.r;
	}
	if (ftx_is_button_press(KEY_DOWN) && (up = 1))
	{
		c.i = (data->args.view_port_down - data->args.view_port_up) / 60;
		data->args.view_port_down += c.i;
		data->args.view_port_up += c.i;
	}
	if (ftx_is_button_press(KEY_UP) && (up = 1))
	{
		c.i = (data->args.view_port_down - data->args.view_port_up) / 60;
		data->args.view_port_down -= c.i;
		data->args.view_port_up -= c.i;
	}
	if (ftx_is_button_press(MICE_LEFT) && (up = 1))
	{
		printf("view_port - left: %f, right: %f, up: %f, down: %f\n", data->args.view_port_left, data->args.view_port_right, data->args.view_port_up, data->args.view_port_down);
		c.r = data->args.view_port_left + (data->args.view_port_right - data->args.view_port_left) * (ftx_mice_position().x / data->args.width);
		c.i = data->args.view_port_up + (data->args.view_port_down - data->args.view_port_up) * (ftx_mice_position().y / data->args.length);
		data->args.view_port_left += c.r;
		data->args.view_port_right += c.r;
		data->args.view_port_up += c.i;
		data->args.view_port_down += c.i;
		printf("view_port - left: %f, right: %f, up: %f, down: %f\n", data->args.view_port_left, data->args.view_port_right, data->args.view_port_up, data->args.view_port_down);
	}
	if (up)
	{
		ftocl_clear_current_kernel_arg(0);
		ftocl_set_current_kernel_arg(CL_MEM_READ_ONLY, 0, sizeof(t_fractol_args),
													&data->args);
	}
	return (up);
}

void	first_args(void)
{
	t_fractol_data	*data;

	data = ft_fractol_data();
	ftocl_set_current_kernel_arg(CL_MEM_READ_ONLY, 0, sizeof(t_fractol_args),
												&data->args);
	ftocl_set_current_kernel_arg(CL_MEM_WRITE_ONLY, 1, data->array_size, NULL);
}

void	fractol(void)
{
	t_window		*win;
	t_image			*info;

	if (ftx_init() == NULL)
		return ;
	if ((win = ftx_create_window("fractol", ft_point(1920, 1080), 60, &fill_fractol)) == NULL)
		return ;
	win->up_func = &update;
	info = ftx_new_image(ft_point(50, 30));
	info->fill_func = &fill_info;
	ftx_add_image(win, info, 1);
	first_args();
	ftx_start();
}

int		main(int argc, char **argv)
{
	int	fd;

	if (argc < 2)
	{
		write(1, "Usage: ", 7);
		write(1, argv[0], ft_strlen(argv[0]));
		write(1, " <arg0> [arg1, ...]\n", 20);
		return (0);
	}
	ft_init();
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return (-1);
	ftocl_make_program((uint64_t*)"fractol ", ft_readfile(fd));
	ftocl_set_current_kernel((uint64_t*)"mandelbr");
	close(fd);
	fractol();
	return (0);
}
