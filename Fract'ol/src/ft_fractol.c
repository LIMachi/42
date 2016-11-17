#include <stdio.h>
#include <libft.h>
#include <libftx.h>
#include <libftocl.h>
#include <fractol.h>

#define WIDTH	(1920 * 1)
#define HEIGHT	(1080 * 1)

void	ft_fractol_data_init(t_fractol_data	*data)
{
	data->args.iterations = 1000;
	data->args.z0 = (t_cl_comp){0, 0};
	data->args.size = (t_cl_point){WIDTH, HEIGHT};
	data->args.vp_ul = (t_cl_comp){-3.0f, -2.0f};
	data->args.vp_dr = (t_cl_comp){3.0f, 2.0f};
	data->array_size = sizeof(cl_int) * WIDTH * HEIGHT;
	data->rbmp = (cl_int*)ft_memalloc(data->array_size);
	data->args.anti_alias = 1;
}

t_fractol_data	*ft_fractol_data(void)
{
	static t_fractol_data	data = {0};

	if (data.args.size.x == 0 && data.args.size.y == 0)
		ft_fractol_data_init(&data);
	return (&data);
}

int		fill_fractol(t_image *img)
{
	static t_fractol_data	*data = NULL;
	int						x;
	int						y;

	if (data == NULL)
		data = ft_fractol_data();
	ftocl_start_current_kernel(1, &data->array_size, NULL);
	ftocl_read_current_kernel_arg(1, data->rbmp);
	y = -1;
	while (++y < data->args.size.y && (x = -1))
		while (++x < data->args.size.x)
			ftx_put_pixel_img(img, x, y, data->rbmp[y * data->args.size.x + x]);
	return (0);
}

int		update(void)
{
	int						up;
	static t_fractol_data	*data = NULL;
	float					c;

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
	if (ftx_is_button_press(KEY_A))
	{
		if (ftx_is_button_press(KEY_PAD_PLUS) && (up = 1))
			data->args.anti_alias += data->args.anti_alias < 4;
		if (ftx_is_button_press(KEY_PAD_MINUS) && (up = 1))
			data->args.anti_alias -= data->args.anti_alias > 1;
	}
	if (ftx_is_button_press(KEY_Z))
	{
		if (ftx_is_button_press(KEY_PAD_PLUS) && (up = 1))
		{
			data->args.vp_ul.r /= 1.5;
			data->args.vp_ul.i /= 1.5;
			data->args.vp_dr.r /= 1.5;
			data->args.vp_dr.i /= 1.5;
		}
		if (ftx_is_button_press(KEY_PAD_MINUS) && (up = 1))
		{
			data->args.vp_ul.r *= 1.5;
			data->args.vp_ul.i *= 1.5;
			data->args.vp_dr.r *= 1.5;
			data->args.vp_dr.i *= 1.5;
		}
	}
	if (ftx_is_button_press(KEY_LEFT) && (up = 1))
	{
		c = -(data->args.vp_dr.r - data->args.vp_ul.r) / 60.0f;
		data->args.vp_dr.r += c;
		data->args.vp_ul.r += c;
	}
	if (ftx_is_button_press(KEY_RIGHT) && (up = 1))
	{
		c = (data->args.vp_dr.r - data->args.vp_ul.r) / 60.0f;
		data->args.vp_dr.r += c;
		data->args.vp_ul.r += c;
	}
	if (ftx_is_button_press(KEY_DOWN) && (up = 1))
	{
		c = (data->args.vp_dr.i - data->args.vp_ul.i) / 60.0f;
		data->args.vp_dr.i += c;
		data->args.vp_ul.i += c;
	}
	if (ftx_is_button_press(KEY_UP) && (up = 1))
	{
		c = -(data->args.vp_dr.i - data->args.vp_ul.i) / 60.0f;
		data->args.vp_dr.i += c;
		data->args.vp_ul.i += c;
	}
	if (ftx_is_button_press(KEY_PAD_0) && (up = 1))
	{
		data->args.iterations = 1000;
		data->args.vp_ul = (t_cl_comp){-3.0f, -2.0f};
		data->args.vp_dr = (t_cl_comp){3.0f, 2.0f};
	}
	if (up)
	{
		ftocl_clear_current_kernel_arg(0);
		ftocl_set_current_kernel_arg(CL_MEM_READ_ONLY, 0,
									sizeof(t_fractol_args), &data->args);
	}
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

	if ((win = ftx_new_window("fractol", ft_point(1920, 1080), 60, &fill_fractol)) == NULL)
		return ;
	win->up_func = &update;
	first_args();
	ftx_start();
}

int		main(int argc, char **argv, char **env)
{
	int	fd;

	if (argc < 3)
	{
		write(1, "Usage: ", 7);
		write(1, argv[0], ft_strlen(argv[0]));
		write(1, " <file.cl> <kernel_id> [options..]\n", 35);
		return (0);
	}
	ft_init(env);
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return (-1);
	ftocl_make_program((uint64_t*)"fractol ", ft_readfile(fd));
	close(fd);
	if (!(fd = ftocl_set_current_kernel((uint64_t*)argv[2])))
		fractol();
	if (fd == 1)
		ft_putendl("There was no fractal correcponding to the id passed in arg");
	ftocl_end();
	return (0);
}
