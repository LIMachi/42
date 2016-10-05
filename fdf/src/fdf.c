/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/15 00:21:53 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/06 00:46:49 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftx.h>

void		ft_update_rotation_matrix(t_mat_r *mat)
{
	t_point3d	s;
	t_point3d	c;

	s = (t_point3d){SIN(mat->r.x), SIN(mat->r.y), SIN(mat->r.z)};
	c = (t_point3d){COS(mat->r.x), COS(mat->r.y), COS(mat->r.z)};
	*mat = (t_mat_r){mat->r,
		{{c.z * c.y, c.z * s.y * s.x - s.z * c.x, c.z * s.y * c.x - s.z * s.x},
		{s.z * c.y, s.z * s.y * s.x + c.x * c.z, s.z * s.y * c.x - c.z * s.x},
		{-s.y, s.x * c.y, c.x * c.y}}};
}

t_point3d	ft_matmultvect(t_mat_r *mat, t_point3d vect, t_point3d center)
{
	t_point3d	tmp;

	tmp = ft_pt3sub(vect, center);
	return ((t_point3d){
		mat->m[0][0] * tmp.x + mat->m[1][0] * tmp.y + mat->m[2][0] * tmp.z
		+ center.x, mat->m[0][1] * tmp.x + mat->m[1][1] * tmp.y + mat->m[2][1]
		* tmp.z + center.y, mat->m[0][2] * tmp.x + mat->m[1][2] * tmp.y
		+ mat->m[2][2] * tmp.z + center.z});
}

t_point	ft_3d_to_2d(t_point3d eye, t_point screen_center, t_point3d point, double zoom)
{
	return ((t_point){zoom * (eye.z * (point.x - eye.x) / (eye.z + point.z) + eye.x) + screen_center.x,
					zoom * (eye.z * (point.y - eye.y) / (eye.z + point.z) + eye.y) + screen_center.y});
}

int		sf_color_mix(int s, int e, t_fix p)
{
	t_fix r;
	t_fix g;
	t_fix b;

	r.FIX_INT = ((s & 0xFF0000) >> 16);
	g.FIX_INT = ((s & 0xFF00) >> 8);
	b.FIX_INT = (s & 0xFF);
	r.i32 += (((e & 0xFF0000) >> 16) - r.FIX_INT) * p.i32;
	g.i32 += (((e & 0xFF00) >> 8) - g.FIX_INT) * p.i32;
	b.i32 += ((e & 0xFF) - b.FIX_INT) * p.i32;
	return (ftx_fixtorgb(r, g, b));
}

#if NORM42 == 0
int	ftx_update(void *ptr)
{
	t_mlx_data		*data;
	t_window		*tmpwin;
	t_image			*tmpimg;
	struct timespec	time;
	int				f;

	data = (t_mlx_data*)ptr;
	clock_gettime(CLOCK_REALTIME, &time);
	tmpwin = data->windows;
	while (tmpwin != NULL)
	{
		f = time.tv_nsec / (1 + 1000000000L / tmpwin->wfps);
		if (f != tmpwin->last_frame || time.tv_sec != tmpwin->last_time.tv_sec)
		{
			if (time.tv_sec != tmpwin->last_time.tv_sec)
			{
				tmpwin->fps = tmpwin->frames;
				tmpwin->frameloss += (tmpwin->frames < tmpwin->wfps);
				tmpwin->frames = 1;
			}
			else
				tmpwin->frames++;
			tmpwin->last_frame = f;
			tmpwin->last_time = time;
			ftx_clear_img(tmpwin->vbuffer);
			if (tmpwin->up_func)
				tmpwin->up_func(tmpwin);
			tmpimg = tmpwin->images;
			while (tmpimg != NULL)
			{
				if (tmpimg->fill_func)
					tmpimg->fill_func(tmpwin, tmpimg);
				if (tmpimg->update && !(tmpimg->update = 0))
					ftx_put_img_to_img(tmpwin->vbuffer, tmpimg, 0);
				tmpimg = tmpimg->next;
			}
			mlx_put_image_to_window(data->mlx, tmpwin->win,
				tmpwin->vbuffer->ptr, tmpwin->vbuffer->pos.x,
				tmpwin->vbuffer->pos.y);
		}
		tmpwin = tmpwin->next;
	}
	return (0);
}
#else
# if OS == LINUX
#  pragma message "Warning: NORM42 will disable the fps stabilisation on Linux."
#  pragma message "Please disable NORM42 (= 0/undef) to allow fps stabilisation"
# endif
int	ftx_update(void *ptr)
{
	t_mlx_data		*data;
	t_window		*tmpwin;
	t_image			*tmpimg;

	data = (t_mlx_data*)ptr;
	tmpwin = data->windows;
	while (tmpwin != NULL)
	{
			ftx_clear_img(tmpwin->vbuffer);
			if (tmpwin->up_func)
				tmpwin->up_func(tmpwin);
			tmpimg = tmpwin->images;
			while (tmpimg != NULL)
			{
				if (tmpimg->fill_func)
					tmpimg->fill_func(tmpwin, tmpimg);
				if (tmpimg->update && !(tmpimg->update = 0))
					ftx_put_img_to_img(tmpwin->vbuffer, tmpimg, 0);
				tmpimg = tmpimg->next;
			}
			mlx_put_image_to_window(data->mlx, tmpwin->win,
				tmpwin->vbuffer->ptr, tmpwin->vbuffer->pos.x,
				tmpwin->vbuffer->pos.y);
		tmpwin = tmpwin->next;
	}
	return (0);
}
#endif

int		fill_fdf(t_window *win, t_image *img)
{
	t_fdf		*fdf;
	t_mlx_data	*data;
	t_point3d	tmp;
	t_point		pos;
	double		tmpd;
	int			up;

	data = ftx_data(GDX_ACCES);
	fdf = (t_fdf*)(win->data);
	if (data ->focused_window == win->id)
	{
		up = 0;
		if (data->keymap[KEY_CTRL_LEFT])
		{
			tmpd = win->zoom;
			win->zoom += data->keymap[KEY_PAD_PLUS] - data->keymap[KEY_PAD_MINUS];
			if (tmpd != win->zoom)
				up = 1;
		}
		if (data->keymap[KEY_X])
		{
			tmpd = fdf->rotation->r.x;
			fdf->rotation->r.x += 0.05 * (data->keymap[KEY_PAD_PLUS] - data->keymap[KEY_PAD_MINUS]);
			fdf->rotation->r.x = data->keymap[KEY_PAD_0] ? 0 : fdf->rotation->r.x;
			if (tmpd != fdf->rotation->r.x)
				up = 1;
		}
		if (data->keymap[KEY_Y])
		{
			tmpd = fdf->rotation->r.y;
			fdf->rotation->r.y += 0.05 * (data->keymap[KEY_PAD_PLUS] - data->keymap[KEY_PAD_MINUS]);
			fdf->rotation->r.y = data->keymap[KEY_PAD_0] ? 0 : fdf->rotation->r.y;
			if (tmpd != fdf->rotation->r.y)
				up = 1;
		}
		if (data->keymap[KEY_Z])
		{
			tmpd = fdf->rotation->r.z;
			fdf->rotation->r.z += 0.05 * (data->keymap[KEY_PAD_PLUS] - data->keymap[KEY_PAD_MINUS]);
			fdf->rotation->r.z = data->keymap[KEY_PAD_0] ? 0 : fdf->rotation->r.z;
			if (tmpd != fdf->rotation->r.z)
				up = 1;
		}
		if (up)
		{
			ft_update_rotation_matrix(fdf->rotation);
			pos.y = -1;
			while (++pos.y < fdf->size.y && (pos.x = -1))
				while (++pos.x < fdf->size.x)
				{
					tmp = ft_matmultvect(fdf->rotation, fdf->map3[pos.y][pos.x], fdf->camera_pos);
					tmp = ft_pt3add(tmp, fdf->camera_pos);
					fdf->map2[pos.y][pos.x] = ft_3d_to_2d((t_point3d){0, 0, 100}, ft_point(win->size.x / 2, win->size.y / 2), tmp, win->zoom);
				}
			pos.y = -1;
			ftx_clear_img(img);
			while (++pos.y < fdf->size.y && (pos.x = -1))
				while (++pos.x < fdf->size.x)
				{
					if (pos.x < fdf->size.x - 1)
						ftx_line(img, fdf->map2[pos.y][pos.x], fdf->map2[pos.y][pos.x + 1], ft_point(fdf->map[pos.y][pos.x][1], fdf->map[pos.y][pos.x + 1][1]));
					if (pos.y < fdf->size.y - 1)
						ftx_line(img, fdf->map2[pos.y][pos.x], fdf->map2[pos.y + 1][pos.x], ft_point(fdf->map[pos.y][pos.x][1], fdf->map[pos.y + 1][pos.x][1]));
				}
		}
	}
	img->update = 1;
	return (0);
}

int		fill_info(t_window *win, t_image *img)
{
	void *tmp;

	ftx_clear_img(img);
	ftx_print_str(img, ft_point(1, 1), WHITE, tmp = ft_itoa(win->fps));
	img->update = 1;
	free(tmp);
	return (0);
}

int		up_fdf(t_window *win)
{
	(void)win;
	return (0);
}

void	main_window_init(int ***map, t_point size)
{
	t_window	*window;
	t_image		*image;
	t_fdf		*fdf;
	int			i;
	int			j;

	window = ftx_new_window(ft_point(1000, 1000), "fdf", 60);
	image = ftx_new_image(ft_point(1000, 1000));
	image->fill_func = fill_fdf;
	ftx_add_image(window, image, 1);
	(image = ftx_new_image(ft_point(200, 100)))->fill_func = fill_info;
	ftx_add_image(window, image, 2);
	window->up_func = up_fdf;
	fdf = (t_fdf*)ft_memalloc(sizeof(t_fdf));
	fdf->map = map;
	fdf->size = size;
	fdf->map3 = (t_point3d**)ft_memalloc(sizeof(t_point3d*) * size.y);
	fdf->map2 = (t_point**)ft_memalloc(sizeof(t_point*) * size.y);
	i = -1;
	while (++i < size.y)
	{
		fdf->map3[i] = (t_point3d*)ft_memalloc(sizeof(t_point3d) * size.x);
		fdf->map2[i] = (t_point*)ft_memalloc(sizeof(t_point) * size.x);
		j = -1;
		while (++j < size.x)
			fdf->map3[i][j] = (t_point3d){j, i, map[i][j][0]};
	}
	fdf->rotation = (t_mat_r*)ft_memalloc(sizeof(t_mat_r));
	fdf->eye = (t_point3d){0, 0, 7};
	window->data = (void*)fdf;
	window->use_code = C_FDF;
	ftx_add_window(window);
	ft_putnbr(window->id);
	ft_putchar('\n');
	mlx_hook(window->win, 2, (1L << 0), ftx_keypress_hook, window);
	mlx_hook(window->win, 3, (1L << 1), ftx_keyrelease_hook, window);
	mlx_hook(window->win, 4, (1L << 2), ftx_buttonpress_hook, window);
	mlx_hook(window->win, 5, (1L << 3), ftx_buttonrelease_hook, window);
	mlx_hook(window->win, 6, (1L << 6), ftx_motion_hook, window);
}

void	term_window_init()
{
	t_window	*window;

	window = ftx_new_window(ft_point(500, 500), "term", 30);
	window->use_code = C_TERM;
	ftx_add_window(window);
	mlx_hook(window->win, 2, (1L << 0), ftx_keypress_hook, window);
	mlx_hook(window->win, 3, (1L << 1), ftx_keyrelease_hook, window);
	mlx_hook(window->win, 4, (1L << 2), ftx_buttonpress_hook, window);
	mlx_hook(window->win, 5, (1L << 3), ftx_buttonrelease_hook, window);
	mlx_hook(window->win, 6, (1L << 6), ftx_motion_hook, window);
}

void	button_window_init()
{
	t_window	*window;

	window = ftx_new_window(ft_point(500, 500), "button", 10);
	window->use_code = C_BUTTON;
	ftx_add_window(window);
	mlx_hook(window->win, 2, (1L << 0), ftx_keypress_hook, window);
	mlx_hook(window->win, 3, (1L << 1), ftx_keyrelease_hook, window);
	mlx_hook(window->win, 4, (1L << 2), ftx_buttonpress_hook, window);
	mlx_hook(window->win, 5, (1L << 3), ftx_buttonrelease_hook, window);
	mlx_hook(window->win, 6, (1L << 6), ftx_motion_hook, window);
}

void	fdf(int ***map, t_point size)
{
	t_mlx_data	*data;

	if ((data = ftx_data(GDX_NEW)) == NULL)
		return ;
	init_mlx_data();
//	(void)map;
//	(void)size;
	main_window_init(map, size);
//	main_window_init(map, size);
//	term_window_init();
//	button_window_init();
	mlx_loop_hook(data->mlx, ftx_update, (void*)data);
	mlx_loop(data->mlx);
}

t_point	fdf_parse_file0(char *filename)
{
	int		fd;
	char	*line;
	t_point	t;

	if ((fd = open(filename, O_RDONLY)) < 0)
		return ((t_point){.x = -1, .y = -1});
	t = ft_point(-1, -1);
	while (get_next_line(fd, &line) == 1 && !(0 * ++t.y))
		if (t.x == -1)
			t.x = ft_strcntw(line);
		else if (t.x != ft_strcntw(line))
			return ((t_point){.x = -1, .y = -1});
	if (t.y == -1)
		return (t);
	close(fd);
	++t.y;
	return (t);
}

int		***fdf_parse_file(int fd, t_point t)
{
	char	*line;
	char	*tmp;
	t_point	i;
	int		***map;

	map = (int ***)ft_tab3dalloc(t.x, t.y, 2, sizeof(int));
	i.y = -1;
	while (get_next_line(fd, &line) == 1 && !(0 * ++i.y))
	{
		tmp = line;
		i.x = 0;
		map[i.y][i.x][0] = ft_atoi(tmp);
		if (ft_strchr(tmp, ',') != NULL &&
				ft_strchr(tmp, ',') < ft_strnw(tmp))
			map[i.y][i.x][1] = ft_atoi(ft_strchr(tmp, ',') + 1);
		else
			map[i.y][i.x][1] = 0x00FFFF;
		while ((tmp = ft_strnw(tmp))[0] != 0 && !(0 * ++i.x))
		{
			map[i.y][i.x][0] = ft_atoi(tmp);
			if (ft_strchr(tmp, ',') != NULL &&
				ft_strchr(tmp, ',') < ft_strnw(tmp))
				map[i.y][i.x][1] = ft_atoi(ft_strchr(tmp, ',') + 1);
			else
				map[i.y][i.x][1] = 0x00FFFF;
		}
		free(line);
	}
	return (map);
}

#include <stdio.h>

int		main(int argc, char **argv)
{
	int		***map;
	t_point	t;
	int		fd;

	if (argc < 2)
	{
		write(1, "Usage: ", 7);
		write(1, argv[0], ft_strlen(argv[0]));
		write(1, " <filename> [arguments]\n", 25);
		return (0);
	}
	printf("%s\n",argv[1]);
	t = fdf_parse_file0(argv[1]);
	if (t.y == -1)
		return (0);
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return (0);
	map = fdf_parse_file(fd, t);
	close(fd);
	fdf(map, t);
	return (0);
}

int	ft_file_seek_forward(int fd, int offset)
{
	char	c;
	int		r;
	int		n;

	if (fd < 0 || offset < 0)
		return (-1);
	n = 0;
	while (offset-- > 0)
		if (++n && (r = read(fd, &c, 1)) < 1)
			return (r == 0 ? n - 1 : -1);
	return (n);
}

/*
int main(int argc, char **argv)
{
	char **data;
	t_bitmap	*truc;
	int i;

	if (argc < 2)
		return (0);
	//data = read_xpm3(argv[1]);
	truc = bitmap_file_load(argv[1]);

	i = 0;
	while (data[i])
		printf("%s\n", data[i++]);
}
*/

/*
int main(int argc, char **argv)
{
	t_bitmap	*test0;
	t_ubmp		*test1;

	if (argc > 1)
		test0 = bitmap_file_load(argv[1]);
	else
		return (0);
	test1 = bitmap_to_ubmp(test0);
	int y = -1;
	while (++y < test1->size.y)
	{
		int x = -1;
		while (++x < test1->size.x)
			printf("%6x ", (unsigned int)test1->data[test1->size.x * y + x]);
		printf("\n");
	}
}
*/

/*
int	main(int argc, char **argv)
{
	char	*file;
	int		size;

	if (argc > 1)
	{
		file = NULL;
		size = ft_bonus_read(argv[1], &file);
		if (size > -1)
			write(1, file, size);
	}
}
*/
