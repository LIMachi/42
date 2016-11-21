#include <stdio.h>
#include <libft.h>
#include <libftx.h>
#include <libftocl.h>
#include <fractol.h>

#define WIDTH	(1920 * 1)
#define HEIGHT	(1080 * 1)

t_fractol_data	*ft_fractol_data(void)
{
	static t_fractol_data	data = {.args = {.iterations = 750u,
		.z0 = (t_cl_comp){0.0f, 0.0f}, .size = (t_cl_point){WIDTH, HEIGHT},
		.vp_ul = (t_cl_comp){-1.77f, -1.0f}, .vp_dr = (t_cl_comp){1.77f, 1.0f},
		.anti_alias = 1u}, .array_size = sizeof(cl_int) * WIDTH * HEIGHT,
		.rbmp = NULL, .lock = 1};

	if (data.rbmp == NULL)
		data.rbmp = (cl_int*)ft_memalloc(data.array_size);
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

void	first_args(void)
{
	t_fractol_data	*data;

	data = ft_fractol_data();
	ftocl_set_current_kernel_arg(CL_MEM_READ_ONLY, 0, sizeof(t_fractol_args),
												&data->args);
	ftocl_set_current_kernel_arg(CL_MEM_WRITE_ONLY, 1, data->array_size, NULL);
	fill_fractol(ftx_data()->focused_window->vbuffer);
	ftx_refresh_window(ftx_data()->focused_window);
}

int	call_key_0(int key, int status, void *data)
{
	int 		up;
	t_window	*win;

	win = (t_window*)data;
	up = 0;
	if (key == KEY_R && status == FTX_KEY_STATUS_PRESSED && (up = 1))
		fill_fractol(win->vbuffer);
	if (key == KEY_B && status == FTX_KEY_STATUS_PRESSED && (up = 1))
		ftx_fill_image(win->vbuffer, 0, 0.01);
	if (key == KEY_W && status == FTX_KEY_STATUS_PRESSED && (up = 1))
		ftx_fill_image(win->vbuffer, 0xFFFFFF, 0.01);
	if (key == KEY_S && status == FTX_KEY_STATUS_PRESSED && *ftx_key_status(KEY_CTRL_LEFT))
		ftx_screenshoot(win, "./");
	if (key == KEY_L && status == FTX_KEY_STATUS_PRESSED)
		ft_fractol_data()->lock = 1 - ft_fractol_data()->lock;
	if (up)
		ftx_refresh_window(win);
	return (0);
}

int	call_key_1(int key, int status, void *data)
{
	int				up;
	t_fractol_data	*f;
	double			c;

	if (status != FTX_KEY_STATUS_PRESSED)
		return (0);
	up = 0;
	f = (t_fractol_data*)data;
	if ((key == KEY_LEFT || *ftx_key_status(KEY_LEFT)) && (up = 1))
	{
		c = -(f->args.vp_dr.r - f->args.vp_ul.r) / 30.0f;
		f->args.vp_dr.r += c;
		f->args.vp_ul.r += c;
	}
	if ((key == KEY_RIGHT || *ftx_key_status(KEY_RIGHT)) && (up = 1))
	{
		c = (f->args.vp_dr.r - f->args.vp_ul.r) / 30.0f;
		f->args.vp_dr.r += c;
		f->args.vp_ul.r += c;
	}
	if ((key == KEY_UP || *ftx_key_status(KEY_UP)) && (up = 1))
	{
		c = -(f->args.vp_dr.i - f->args.vp_ul.i) / 30.0f;
		f->args.vp_dr.i += c;
		f->args.vp_ul.i += c;
	}
	if ((key == KEY_DOWN || *ftx_key_status(KEY_DOWN)) && (up = 1))
	{
		c = (f->args.vp_dr.i - f->args.vp_ul.i) / 30.0f;
		f->args.vp_dr.i += c;
		f->args.vp_ul.i += c;
	}
	if (key == KEY_PAD_0 && (up = 1))
	{
		f->args = (t_fractol_args){.iterations = 750u,
			.z0 = (t_cl_comp){0.0f, 0.0f},
			.size = (t_cl_point){WIDTH, HEIGHT},
			.vp_ul = (t_cl_comp){-1.77f, -1.0f},
			.vp_dr = (t_cl_comp){1.77f, 1.0f},
			.anti_alias = 1u};
		f->lock = 1;
	}
	if (*ftx_key_status(KEY_I) && key == KEY_PAD_PLUS && (up = 1))
		f->args.iterations = (f->args.iterations += 1 + 9 * (f->args.iterations > 20) + 90 * (f->args.iterations > 400)) < 5000 ? f->args.iterations : 5000;
	if (*ftx_key_status(KEY_I) && key == KEY_PAD_MINUS && (up = 1))
		f->args.iterations = (f->args.iterations -= 1 + 9 * (f->args.iterations > 20) + 90 * (f->args.iterations > 500)) > 0 ? f->args.iterations : 1;
	if (*ftx_key_status(KEY_I))
	{
		ft_putnbr(f->args.iterations);
		ft_putchar('\n');
	}
	if (up)
	{
		ftocl_clear_current_kernel_arg(0);
		ftocl_set_current_kernel_arg(CL_MEM_READ_ONLY, 0,
									sizeof(t_fractol_args), &f->args);
		fill_fractol(ftx_data()->focused_window->vbuffer);
		ftx_refresh_window(ftx_data()->focused_window);
	}
	return (0);
}

int	call_exit(int key, int status, void *data)
{
	(void)data;
	if (key == KEY_EXIT && status == FTX_KEY_STATUS_PRESSED)
		exit(0);
	return (0);
}

t_cl_comp	mice_to_comp(void)
{
	t_fractol_args	*args;
	t_point			mice;
	t_cl_comp		p;
	t_cl_comp		s;

	args = &ft_fractol_data()->args;
	mice = ftx_data()->focused_window->mice.pos;
	p = (t_cl_comp){.r = (cl_float)mice.x / (cl_float)args->size.x,
					.i = (cl_float)mice.y / (cl_float)args->size.y};
	s = (t_cl_comp){.r = args->vp_dr.r - args->vp_ul.r,
					.i = args->vp_dr.i - args->vp_ul.i};
	return ((t_cl_comp){
		.r = args->vp_ul.r + s.r * p.r,
		.i = args->vp_ul.i + s.i * p.i});
}

int	call_mice_move(t_point pos, t_point click_pos, void *data)
{
	(void)data;
	if (*ftx_button_status(MICE_LEFT))
	{
		fill_fractol(ftx_data()->focused_window->vbuffer);
		ftx_put_selection_square(ftx_data()->focused_window->vbuffer, pos, click_pos, 0x7777FF);
		ftx_refresh_window(ftx_data()->focused_window);
	}
	if (ft_fractol_data()->lock == 0)
	{
		ft_fractol_data()->args.z0 = mice_to_comp();
		ftocl_clear_current_kernel_arg(0);
		ftocl_set_current_kernel_arg(CL_MEM_READ_ONLY, 0,
						sizeof(t_fractol_args), &ft_fractol_data()->args);
		fill_fractol(ftx_data()->focused_window->vbuffer);
		ftx_refresh_window(ftx_data()->focused_window);
	}
	return (0);
}

#define FRACTOL_KEEP_RATIO 0

void	view_port_cut(t_fractol_args *args, t_point a, t_point b)
{
	t_cl_comp	tmp_ul;
	t_cl_comp	tmp_dr;
	cl_float	r;
	t_point		t;

	if (ft_point_equal(a, b))
		return ;
	if (a.x > b.x)
	 	ft_int_swap(&a.x, &b.x);
	if (a.y > b.y)
		ft_int_swap(&a.y, &b.y);
	if (FRACTOL_KEEP_RATIO)
	{
		(void)(r = (cl_float)args->size.x / (cl_float)args->size.y);
		(void)(t = ft_point_difference(a, b));
//		if (t.x * r > t.y)

	}
	tmp_ul.r = args->vp_ul.r + (args->vp_dr.r - args->vp_ul.r) * ((cl_float)a.x / (cl_float)args->size.x);
	tmp_dr.r = args->vp_ul.r + (args->vp_dr.r - args->vp_ul.r) * ((cl_float)b.x / (cl_float)args->size.x);
	tmp_ul.i = args->vp_ul.i + (args->vp_dr.i - args->vp_ul.i) * ((cl_float)a.y / (cl_float)args->size.y);
	tmp_dr.i = args->vp_ul.i + (args->vp_dr.i - args->vp_ul.i) * ((cl_float)b.y / (cl_float)args->size.y);
	args->vp_ul = tmp_ul;
	args->vp_dr = tmp_dr;
}

void	zoom(cl_float zoom)
{
	t_fractol_args	*args;
	t_point			mice;
	t_cl_comp		p;
	t_cl_comp		s;

	args = &ft_fractol_data()->args;
	mice = ftx_data()->focused_window->mice.pos;
	p = (t_cl_comp){.r = (cl_float)mice.x / (cl_float)args->size.x,
					.i = (cl_float)mice.y / (cl_float)args->size.y};
	s = (t_cl_comp){.r = args->vp_dr.r - args->vp_ul.r,
					.i = args->vp_dr.i - args->vp_ul.i};
	s = (t_cl_comp){.r = s.r * zoom - s.r, .i = s.i * zoom - s.i};
	args->vp_dr.r -= (1.0f - p.r) * s.r;
	args->vp_ul.r += p.r * s.r;
	args->vp_dr.i -= (1.0f - p.i) * s.i;
	args->vp_ul.i += p.i * s.i;
}

int	call_mice_button(int button, int status, void *data)
{
	int				up;
	t_fractol_data	*f;
	t_window		*win;

	up = 0;
	f = ft_fractol_data();
	win = (t_window*)data;
	if (button == MICE_SCROLL_UP && status == FTX_KEY_STATUS_PRESSED && (up = 1))
	{
		zoom(1.1f);
//		f->args.vp_ul.r /= 1.5;
//		f->args.vp_ul.i /= 1.5;
//		f->args.vp_dr.r /= 1.5;
//		f->args.vp_dr.i /= 1.5;
	}
	if (button == MICE_SCROLL_DOWN && status == FTX_KEY_STATUS_PRESSED && (up = 1))
	{
		zoom(1.0f / 1.1f);
//		f->args.vp_ul.r *= 1.5;
//		f->args.vp_ul.i *= 1.5;
//		f->args.vp_dr.r *= 1.5;
//		f->args.vp_dr.i *= 1.5;
	}
	if (button == MICE_LEFT && status == FTX_KEY_STATUS_RELEASED && (up = 1))
	{
		view_port_cut(&f->args, win->mice.click_pos, win->mice.pos);
	}
	if (up)
	{
		ftocl_clear_current_kernel_arg(0);
		ftocl_set_current_kernel_arg(CL_MEM_READ_ONLY, 0,
									sizeof(t_fractol_args), &f->args);
		fill_fractol(ftx_data()->focused_window->vbuffer);
		ftx_refresh_window(ftx_data()->focused_window);
	}
	return (0);
}

void	fractol(void)
{
	t_window		*win;

	if ((win = ftx_new_window(ft_point(1920, 1080), "fractol",
								(const uint64_t *)"fractol")) == NULL)
		return ;
	ftx_key_hook(KEY_EXIT, &call_exit, NULL);
	ftx_key_hook(KEY_R, &call_key_0, ftx_data()->focused_window);
	ftx_key_hook(KEY_B, &call_key_0, ftx_data()->focused_window);
	ftx_key_hook(KEY_W, &call_key_0, ftx_data()->focused_window);
	ftx_key_hook(KEY_S, &call_key_0, ftx_data()->focused_window);
	ftx_key_hook(KEY_L, &call_key_0, ftx_data()->focused_window);
	ftx_key_hook(KEY_LEFT, &call_key_1, ft_fractol_data());
	ftx_key_hook(KEY_RIGHT, &call_key_1, ft_fractol_data());
	ftx_key_hook(KEY_UP, &call_key_1, ft_fractol_data());
	ftx_key_hook(KEY_DOWN, &call_key_1, ft_fractol_data());
	ftx_key_hook(KEY_PAD_0, &call_key_1, ft_fractol_data());
	ftx_key_hook(KEY_PAD_PLUS, &call_key_1, ft_fractol_data());
	ftx_key_hook(KEY_PAD_MINUS, &call_key_1, ft_fractol_data());
//	ftx_key_hook(KEY_CTRL_LEFT, NULL, NULL);
	ftx_hook_mice_move(win, &call_mice_move, NULL);
	ftx_hook_mice_button(win, MICE_LEFT, &call_mice_button, win);
	ftx_hook_mice_button(win, MICE_SCROLL_DOWN, &call_mice_button, win);
	ftx_hook_mice_button(win, MICE_SCROLL_UP, &call_mice_button, win);
	first_args();
	ftx_start();
}

/*
** return print all kernel names found in source and return the number of
** names print this way (return -1 on error)
*/

int		print_kernel_names(const char *ocl_src)
{
	char	*tmp;
	int		out;
	char	name_buff[128];
	int		i;

	tmp = ((char*)ocl_src) - 1;
	out = 0;
	while ((tmp = ft_strstr(tmp + 1, "__kernel")) != NULL && ++out)
	{
		tmp += 8;
		while (ft_isspace(*tmp))
			++tmp;
		while (ft_isalnum(*tmp))
			++tmp;
		while (ft_isspace(*tmp))
			++tmp;
		i = 0;
		while (ft_isunix(*tmp) && i < 127)
			name_buff[i++] = *tmp++;
		name_buff[i] = '\0';
		ft_putendl(name_buff);
	}
	return (out);
}

/*
** ft_str_clear_commentaries will set all character in comentaries to ' '
** (except '\n')
*/

char	*ft_str_clear_commentaries(char *str)
{
	char	*out;

	out = str;
	while (*str != '\0')
		if (*str++ == '/' && (*str == '/' || *str == '*') && (str[-1] = ' '))
		{
			if (*str == '/')
				while (*str != '\0' && *str != '\n' && (*str = ' '))
					++str;
			else if (*str == '*')
			{
				while (*str != '\0' && !(str[-1] == '*' && *str == '/'))
					if (*(str++ - 1) != '\n')
						str[-2] = ' ';
				if (str[-1] != '\n')
					str[-1] = ' ';
			}
		}
	return (out);
}

int		print_usage(char *name)
{
	char	*tmp;
	int		fd;

	ft_putstr("Usage: ");
	if ((tmp = ft_strrchr(name, '/')) == NULL)
		ft_putstr(name);
	else
		ft_putstr(tmp + 1);
	ft_putstr(" [source.cl] <kernel_id> [kernel_id..]\n");
	ft_putstr("Kernel ids found in default ./scl/fractol.cl:\n");
	if ((fd = open("./scl/fractol.cl", O_RDONLY)) == -1)
		ft_putstr("./scl/fractol.cl can't be oppened\n");
	else
	{
		if ((tmp = ft_readfile(fd)) == NULL)
			ft_putstr("./scl/fractol.cl can't be read\n");
		close(fd);
		if (print_kernel_names(ft_str_clear_commentaries(tmp)) == 0)
			ft_putstr("Can't find kernel names in ./scl/fractol.cl\n");
		ft_free(tmp);
	}
	ft_end();
	return (0);
}

int		main(int argc, char **argv, char **env)
{
	int	fd;

	ft_init(env);
	if (argc < 2 || argc > 3)
		return (print_usage(argv[0]));
	if (argc == 3)
	{
		if ((fd = open(argv[1], O_RDONLY)) == -1)
			return (-1);
	}
	else
	{
		if ((fd = open("./scl/fractol.cl", O_RDONLY)) == -1)
			return (-1);
	}
	ftocl_make_program(ftocl_str_to_id64("fractol"), ft_str_clear_commentaries(ft_readfile(fd)));
	close(fd);
	ft_fractol_data()->lock = ftocl_str_to_id64(argv[argc - 1]) != ftocl_str_to_id64("julia");
	if (!(fd = ftocl_set_current_kernel(ftocl_str_to_id64(argv[argc - 1]))))
		fractol();
	if (fd == 1)
		ft_putendl("There was no fractal correcponding to the id passed in arg");
	ftocl_end();
	return (0);

}
