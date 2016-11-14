#include <stdio.h>
#include <libft.h>
#include <libftx.h>
#include <libftocl.h>
#include <fractol.h>

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
