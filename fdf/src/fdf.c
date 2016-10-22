/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/15 00:21:53 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/22 05:22:23 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftx.h>

/*
** map format [y][x][d]
*/

void			ft_free_object3d(t_object3d	*object)
{
	if (object == NULL)
		return ;
	if (object->points3d_original != NULL)
		free(object->points3d_original);
	if (object->colors != NULL)
		free(object->colors);
	if (object->points3d != NULL)
		free(object->points3d);
	if (object->points2d != NULL)
		free(object->points2d);
	if (object->lines != NULL)
		free(object->lines);
	free(object);
}

t_object3d		*ft_new_object3d(t_vector position, int nb_points, int nb_lines)
{
	t_object3d	*out;

	if ((out = (t_object3d*)malloc(sizeof(t_object3d))) == NULL)
		return (NULL);
	if (((out->points3d_original = (t_vector*)malloc(sizeof(t_vector) *
			nb_points)) == NULL) || ((out->colors = (int*)malloc(sizeof(int) *
			nb_points)) == NULL) || ((out->points3d = (t_vector*)malloc(sizeof(
			t_vector) * nb_points)) == NULL) || ((out->points2d =
			(t_point*)malloc(sizeof(t_point) * nb_points)) == NULL) ||
			(out->lines = (t_line_ref*)malloc(sizeof(t_line_ref)
			* nb_lines)) == NULL)
	{
		ft_free_object3d(out);
		return (NULL);
	}
	out->object.axis_x = (t_vector){1, 0, 0};
	out->object.axis_y = (t_vector){0, 1, 0};
	out->object.axis_z = (t_vector){0, 0, 1};
	out->object.orientation = (t_quaternion){1, 0, 0, 0};
	out->object.position = position;
	out->nb_points = nb_points;
	out->nb_lines = nb_lines;
	return (out);
}

/*
t_object3d		*ft_object3d_from_fdf(int ***map, t_point size)
{
	t_object3d	*out;
	t_point		pos;

	if (size.x <= 0 || size.y <= 0 || map == NULL || *map == NULL ||
		**map == NULL || (out = ft_new_object3d((t_vector){0, 0, 0}, size.x *
		size.y, (size.x - 1) * size.y + (size.y - 1) * size.x)) == NULL)
		return (NULL);
	pos.y = -1;
	while (++pos.y < size.y && (pos.x = -1))
		while (++pos.x < size.x)
		{

		}
}
*/

t_point	ft_3d_to_2d(t_vector eye, t_point screen_center, t_vector point, double zoom)
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

#define SPEED 1

/*
** the order of rotation applied is roll yaw pitch (or z y x)
*/

/*
t_quaternion	cam_rotate(t_quaternion origin, double yaw, double pitch, double roll)
{
	t_quaternion	rotation;
	t_vector		up;
	t_vector		look;
	t_vector		forward;
	t_vector		side;
	t_matrix		*tmp_mat;

	up = ft_vector(0, 1, 0); //need to be corrected
	tmp_mat = ft_quat_rotation_to_matrix(origin);
	look = ft_vector(0, 0, 1);
	ft_matrix_multply_vector(&look, tmp_mat);
	ft_matrix_free(tmp_mat);
	forward = ft_vector_normalize(ft_vector(look.x, 0, look.z));
	side = ft_vector_cross_product(up, forward);
	rotation = origin;
	rotation = ft_quat_multiply(ft_quat_rotation_build(roll, forward),
																	rotation);
	rotation = ft_quat_multiply(ft_quat_rotation_build(yaw, up), rotation);
	rotation = ft_quat_multiply(ft_quat_rotation_build(pitch, side),
																	rotation);
	return (rotation);
}
*/
/*
t_quaternion	cam_rotate(t_quaternion origin, double pitch, double roll, double yaw)
{
double cr, cp, cy, sr, sp, sy, cpcy, spsy;
t_quaternion out;
(void)origin;
// calculate trig identities
cr = ft_cos(roll/2);
cp = ft_cos(pitch/2);
cy = ft_cos(yaw/2);
sr = ft_sin(roll/2);
sp = ft_sin(pitch/2);
sy = ft_sin(yaw/2);

cpcy = cp * cy;
spsy = sp * sy;
out.r = cr * cpcy + sr * spsy;
out.i = sr * cpcy - cr * spsy;
out.j = cr * sp * cy + sr * cp * sy;
out.k = cr * cp * sy - sr * sp * cy;
return (out);
}
*/
int		fill_fdf(t_window *win, t_image *img)
{
	t_fdf			*fdf;
	t_mlx_data		*data;
	t_vector		tmp;
	t_point			pos;
	double			tmpd;
	int				up;
	t_quaternion	q;
	t_quaternion	r;

	data = ftx_data(GDX_ACCES);
	fdf = (t_fdf*)(win->data);
	if (data ->focused_window == win->id)
	{
		up = 0; //bug ici, non synchrone avec l'update d'écran
		if (data->keymap[KEY_CTRL_LEFT])
		{
			tmpd = win->zoom;
			win->zoom += data->keymap[KEY_PAD_PLUS] - data->keymap[KEY_PAD_MINUS];
			if (tmpd != win->zoom)
				up = 1;
		}
///*
		if (data->keymap[KEY_X])
		{
//			tmp = fdf->camera.object.axis_x;
			tmp = ft_vector(1, 0, 0);
			r = ft_quat_rotation_build(0.05 * (data->keymap[KEY_PAD_PLUS] - data->keymap[KEY_PAD_MINUS]), tmp);
			//fdf->rotation = ft_quat_multiply(fdf->rotation, q);
			q = fdf->camera.object.orientation;
			fdf->camera.object.orientation = ft_quat_multiply(q, r);
//			fdf->camera.yaw += 0.05 * (data->keymap[KEY_PAD_PLUS] - data->keymap[KEY_PAD_MINUS]);
			up = 1;
		}
		else
		if (data->keymap[KEY_Y])
		{
//			tmp = fdf->camera.object.axis_y;
			tmp = ft_vector(0, 1, 0);
			r = ft_quat_rotation_build(0.05 * (data->keymap[KEY_PAD_PLUS] - data->keymap[KEY_PAD_MINUS]), tmp);
			//fdf->rotation = ft_quat_multiply(fdf->rotation, q);
			q = fdf->camera.object.orientation;
			fdf->camera.object.orientation = ft_quat_multiply(q, r);
//			fdf->camera.pitch += 0.05 * (data->keymap[KEY_PAD_PLUS] - data->keymap[KEY_PAD_MINUS]);
			up = 1;
		}
		else
		if (data->keymap[KEY_Z])
		{
//			tmp = fdf->camera.object.axis_z;
			tmp = ft_vector(0, 0, 1);
			r = ft_quat_rotation_build(0.05 * (data->keymap[KEY_PAD_PLUS] - data->keymap[KEY_PAD_MINUS]), tmp);
			//fdf->rotation = ft_quat_multiply(fdf->rotation, q);
			q = fdf->camera.object.orientation;
			fdf->camera.object.orientation = ft_quat_multiply(q, r);
//			fdf->camera.roll += 0.05 * (data->keymap[KEY_PAD_PLUS] - data->keymap[KEY_PAD_MINUS]);
			up = 1;
		}
//*/
/*
		if (data->keymap[KEY_X] || data->keymap[KEY_Y] || data->keymap[KEY_Z])
		{
			if (data->keymap[KEY_X])
				tmp = fdf->camera.object.axis_x;
//				tmp = (t_vector){1, 0, 0};
			else
			if (data->keymap[KEY_Y])
				tmp = fdf->camera.object.axis_y;
//				tmp = (t_vector){0, 1, 0};
			else
			if (data->keymap[KEY_Z])
				tmp = fdf->camera.object.axis_z;
//				tmp = (t_vector){0, 0, 1};
			r = ft_quat_rotation_build(0.05 * (data->keymap[KEY_PAD_PLUS] - data->keymap[KEY_PAD_MINUS]), tmp);
			q = fdf->camera.object.orientation;
			fdf->camera.object.orientation = ft_quat_multiply(q, r);
			up = 1;
		}
*/
/*
		if (data->keymap[KEY_SPACE] && (up = 1))
			fdf->camera.object.position.y += SPEED;
		if (data->keymap[KEY_SHIFT_LEFT] && (up = 1))
			fdf->camera.object.position.y -= SPEED;
		if (data->keymap[KEY_W] && (up = 1))
			fdf->camera.object.position.z -= SPEED;
		if (data->keymap[KEY_S] && (up = 1))
			fdf->camera.object.position.z += SPEED;
		if (data->keymap[KEY_D] && (up = 1))
			fdf->camera.object.position.x -= SPEED;
		if (data->keymap[KEY_A] && (up = 1))
			fdf->camera.object.position.x += SPEED;
*/
///*
		if (data->keymap[KEY_D] && (up = 1))
			fdf->camera.object.position = ft_vector_add(fdf->camera.object.position, ft_vector_scale(fdf->camera.object.axis_x, SPEED));
		if (data->keymap[KEY_A] && (up = 1))
			fdf->camera.object.position = ft_vector_add(fdf->camera.object.position, ft_vector_scale(fdf->camera.object.axis_x, -SPEED));
		if (data->keymap[KEY_SHIFT_LEFT] && (up = 1))
			fdf->camera.object.position = ft_vector_add(fdf->camera.object.position, ft_vector_scale(fdf->camera.object.axis_y, SPEED));
		if (data->keymap[KEY_SPACE] && (up = 1))
			fdf->camera.object.position = ft_vector_add(fdf->camera.object.position, ft_vector_scale(fdf->camera.object.axis_y, -SPEED));
		if (data->keymap[KEY_W] && (up = 1))
			fdf->camera.object.position = ft_vector_add(fdf->camera.object.position, ft_vector_scale(fdf->camera.object.axis_z, SPEED));
		if (data->keymap[KEY_S] && (up = 1))
			fdf->camera.object.position = ft_vector_add(fdf->camera.object.position, ft_vector_scale(fdf->camera.object.axis_z, -SPEED));
//*/
		if (data->keymap[KEY_PAD_0] && (up = 1))
		{
			fdf->camera.object.position = ft_vector(0, 0, 0);
			fdf->camera.object.orientation = ft_quat(1, 0, 0, 0);
			fdf->camera.object.axis_x = ft_vector(1, 0, 0);
			fdf->camera.object.axis_y = ft_vector(0, 1, 0);
			fdf->camera.object.axis_z = ft_vector(0, 0, 1);
			fdf->camera.yaw = 0;
			fdf->camera.pitch = 0;
			fdf->camera.roll = 0;
			win->zoom = 10;
		}
		if (up)
		{
			t_matrix *tmat = NULL;
///*
			if ((data->keymap[KEY_X] || data->keymap[KEY_Y] || data->keymap[KEY_Z]) && (data->keymap[KEY_PAD_MINUS] || data->keymap[KEY_PAD_PLUS]))
			{
//				fdf->camera.object.orientation = ft_quat_inverse(cam_rotate(ft_quat(1, 0, 0, 0), fdf->camera.yaw, fdf->camera.pitch, fdf->camera.roll));
				q = ft_quat_inverse(fdf->camera.object.orientation);
				tmat = ft_quat_rotation_to_matrix(fdf->camera.object.orientation);
				fdf->camera.object.axis_x = ft_vector(1, 0, 0);
				fdf->camera.object.axis_y = ft_vector(0, 1, 0);
				fdf->camera.object.axis_z = ft_vector(0, 0, 1);
				ft_matrix_multply_vector(&(fdf->camera.object.axis_x), tmat);
				ft_matrix_multply_vector(&(fdf->camera.object.axis_y), tmat);
				ft_matrix_multply_vector(&(fdf->camera.object.axis_z), tmat);
				ft_matrix_free(tmat);
			}
			else
				q = ft_quat_inverse(fdf->camera.object.orientation);
//*/
//			q = fdf->camera.object.orientation = cam_rotate(ft_quat(1, 0, 0, 0), fdf->camera.yaw, fdf->camera.pitch, fdf->camera.roll);
			tmat = ft_quat_rotation_to_matrix(q);
			pos.y = -1;
			while (++pos.y < fdf->size.y && (pos.x = -1))
				while (++pos.x < fdf->size.x)
				{
					tmp = fdf->map3[pos.y][pos.x];
					tmp = ft_vector_substract(tmp, (t_vector){0, 0, -100});
					tmp = ft_vector_substract(tmp, fdf->camera.object.position);
					ft_matrix_multply_vector(&tmp, tmat);
					tmp = ft_vector_add(tmp, (t_vector){0, 0, -100});
//					tmp = ft_vector_add(tmp, fdf->camera.object.position);
//					tmp = ft_matmultvect(fdf->rotation, fdf->map3[pos.y][pos.x], fdf->camera_pos);
//					tmp = ft_pt3add(tmp, fdf->camera_pos);
					fdf->map2[pos.y][pos.x] = ft_3d_to_2d((t_vector){0, 0, 100}, ft_point(win->size.x / 2, win->size.y / 2), tmp, win->zoom);
				}
			ft_matrix_free(tmat);
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

	t_camera cam = ((t_fdf*)(win->data))->camera;

	ftx_clear_img(img);
	ftx_print_str(img, ft_point(1, 1), WHITE, tmp = ft_itoa(win->fps));
	free(tmp);

	ftx_print_str(img, ft_point(1, 11), WHITE, "x - yaw: ");
	ftx_print_str(img, ft_point(70, 11), WHITE, tmp = ft_itoa(DEGRE(cam.yaw)));
	free(tmp);

	ftx_print_str(img, ft_point(1, 21), WHITE, "y - pitch: ");
	ftx_print_str(img, ft_point(70, 21), WHITE, tmp = ft_itoa(DEGRE(cam.pitch)));
	free(tmp);

	ftx_print_str(img, ft_point(1, 31), WHITE, "z - roll: ");
	ftx_print_str(img, ft_point(70, 31), WHITE, tmp = ft_itoa(DEGRE(cam.roll)));
	free(tmp);

	ftx_print_str(img, ft_point(1, 41), WHITE, "pos: ");
	ftx_print_str(img, ft_point(50, 41), WHITE, tmp = ft_itoa(cam.object.position.x)); free(tmp);
	ftx_print_str(img, ft_point(70, 41), WHITE, tmp = ft_itoa(cam.object.position.y)); free(tmp);
	ftx_print_str(img, ft_point(90, 41), WHITE, tmp = ft_itoa(cam.object.position.z)); free(tmp);

	img->update = 1;
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
	fdf->map3 = (t_vector**)ft_memalloc(sizeof(t_vector*) * size.y);
	fdf->map2 = (t_point**)ft_memalloc(sizeof(t_point*) * size.y);
	i = -1;
	while (++i < size.y)
	{
		fdf->map3[i] = (t_vector*)ft_memalloc(sizeof(t_vector) * size.x);
		fdf->map2[i] = (t_point*)ft_memalloc(sizeof(t_point) * size.x);
		j = -1;
		while (++j < size.x)
			fdf->map3[i][j] = (t_vector){j, i, map[i][j][0]};
	}
	fdf->camera.object.position = ft_vector(0, 0, 0);
	fdf->camera.object.orientation = ft_quat(1, 0, 0, 0);
	fdf->camera.object.axis_x = ft_vector(1, 0, 0);
	fdf->camera.object.axis_y = ft_vector(0, 1, 0);
	fdf->camera.object.axis_z = ft_vector(0, 0, 1);
	fdf->camera.yaw = 0;
	fdf->camera.pitch = 0;
	fdf->camera.roll = 0;
	window->zoom = 10;
	fdf->eye = (t_vector){0, 0, 7};
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

	ft_init();
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
