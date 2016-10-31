/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/15 00:21:53 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/31 14:32:42 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftx.h>
#include <stdio.h>

/*
** map format [y][x][d]
*/

t_vector	ft_vector_middle(const t_vector a, const t_vector b)
{
	return (ft_vector((b.x + a.x) / 2,
					(b.y + a.y) / 2,
					(b.z + a.z) / 2));
}

t_point	ft_point_middle(const t_point a, const t_point b)
{
	return (ft_point((b.x + a.x) / 2, (b.y + a.y) / 2));
}

t_vector		ft_vector_from_a_to_b(t_vector a, t_vector b)
{
	return (ft_vector_substract(b, a));
}

t_point	ft_3d_to_2d(t_vector eye, t_point screen_center, t_vector point, double zoom)
{
	double tmp;
	(void)zoom;
//	return ((t_point){/*zoom * */ (eye.z * (point.x - eye.x) / (eye.z + point.z) + eye.x) + screen_center.x,
//					/*zoom * */ (eye.z * (point.y - eye.y) / (eye.z + point.z) + eye.y) + screen_center.y});
	if (eye.z + point.z > -0.0001 && eye.z + point.z < 0.0001) //security
		return (ft_point(0, 0));
	tmp = eye.z / (eye.z + point.z);
	return (
		ft_point(point.x * tmp + screen_center.x,
				point.y * tmp + screen_center.y));
}



t_frustrum	ft_frustrum(t_point dl, t_point ur, t_point nf, t_vector focal)
{
	t_vector	ndl;
	t_vector	nur;
	t_vector	fdl;
	t_vector	fur;
	t_frustrum	out;
	double		tmp;

//	fdl = ft_vector(dl.x * (1 + 1 / focal.z), dl.y * (1 + 1 / focal.z), nf.y);
//	fur = ft_vector(ur.x * (1 + 1 / focal.z), ur.y * (1 + 1 / focal.z), nf.y);
	tmp = (focal.z + nf.y) / focal.z;
	fdl = ft_vector(tmp * dl.x, tmp * dl.y, nf.y);
	fur = ft_vector(tmp * ur.x, tmp * ur.y, nf.y);
	tmp = (focal.z + nf.x) / focal.z;
	ndl = ft_vector(tmp * dl.x, tmp * dl.y, nf.x);
	nur = ft_vector(tmp * ur.x, tmp * ur.y, nf.x);
//	(void)focal;
//	fdl = ft_vector(dl.x, dl.y, nf.y);
//	fur = ft_vector(ur.x, ur.y, nf.y);
	out.near_point = ft_vector_middle(
						ft_vector(ndl.x, ndl.y, nf.x),
						ft_vector(nur.x, nur.y, nf.x));
	out.far_point = ft_vector_middle(
						ft_vector(fdl.x, fdl.y, nf.y),
						ft_vector(fur.x, fur.y, nf.y));

	out.bottom_point = ft_vector_middle(
						ft_vector((ndl.x + nur.x) / 2, ndl.y, nf.x),
						ft_vector((fdl.x + fur.x) / 2, fdl.y, nf.y));

	out.top_point = ft_vector_middle(
						ft_vector((ndl.x + nur.x) / 2, nur.y, nf.x),
						ft_vector((fdl.x + fur.x) / 2, fur.y, nf.y));

	out.left_point = ft_vector_middle(
						ft_vector(ndl.x, (ndl.y + nur.y) / 2, (nf.x + nf.y) / 2),
						ft_vector(fdl.x, (fur.y + fdl.y) / 2, (nf.y + nf.x) / 2));

	out.right_point = ft_vector_middle(
						ft_vector(nur.x, (ndl.y + nur.y) / 2, (nf.x + nf.y) / 2),
						ft_vector(fur.x, (fur.y + fdl.y) / 2, (nf.y + nf.x) / 2));

	out.near_normal = ft_vector_add(
							out.near_point,
								ft_vector_normalize(
									ft_vector_cross_product(
										ft_vector_from_a_to_b(
											out.near_point,
											ft_vector(ndl.x, nur.y, nf.x)),
										ft_vector_from_a_to_b(
											out.near_point,
											ft_vector(ndl.x, ndl.y, nf.x)))));

	out.far_normal = ft_vector_add(
							out.far_point,
							ft_vector_normalize(
								ft_vector_cross_product(
									ft_vector_from_a_to_b(
										out.far_point,
										ft_vector(fdl.x, fdl.y, nf.y)),
									ft_vector_from_a_to_b(
										out.far_point,
										ft_vector(fdl.x, fur.y, nf.y)))));

	out.right_normal = ft_vector_add(
							out.right_point,
							ft_vector_normalize(
								ft_vector_cross_product(
									ft_vector_from_a_to_b(
										out.right_point,
										ft_vector(fur.x, fur.y, nf.y)),
									ft_vector_from_a_to_b(
										out.right_point,
										ft_vector(nur.x, ndl.y, nf.x)))));

	out.left_normal = ft_vector_add(
							out.left_point,
							ft_vector_normalize(
								ft_vector_cross_product(
									ft_vector_from_a_to_b(
										out.left_point,
										ft_vector(fdl.x, fdl.y, nf.y)),
									ft_vector_from_a_to_b(
										out.left_point,
										ft_vector(ndl.x, ndl.y, nf.x)))));

	out.top_normal = ft_vector_add(
							out.top_point,
								ft_vector_normalize(
									ft_vector_cross_product(
										ft_vector_from_a_to_b(
											out.top_point,
											ft_vector(nur.x, nur.y, nf.x)),
										ft_vector_from_a_to_b(
											out.top_point,
											ft_vector(fur.x, fur.y, nf.y)))));

	out.bottom_normal = ft_vector_add(
							out.bottom_point,
								ft_vector_normalize(
									ft_vector_cross_product(
										ft_vector_from_a_to_b(
											out.bottom_point,
											ft_vector(fdl.x, fdl.y, nf.y)),
										ft_vector_from_a_to_b(
											out.bottom_point,
											ft_vector(fur.x, fdl.y, nf.y)))));

	return (out);
}
/*
t_frustrum	ft_frustrum()
{
	t_frustrum	out;

	out.near_point = ft_vector(0, 0, 1);
	out.near_normal = ft_vector(0, 0, 2);
	out.far_point = ft_vector(0, 0, 200);
	out.far_normal = ft_vector(0, 0, 199);
	out.bottom_point = ft_vector(0, -50, 100);
	out.bottom_normal = ft_vector(0, -49.8, 101);
	out.top_point = ft_vector(0, 50, 100);
	out.top_normal = ft_vector(0, 49.8, 101);
	out.left_point = ft_vector(-50, 0, 100);
	out.left_normal = ft_vector(-49.8, 0, 101);
	out.right_point = ft_vector(50, 0, 100);
	out.right_normal = ft_vector(49.8, 0, 101);
	return (out);
}
*/

int				ft_is_in_frustrum(t_frustrum frustrum, t_vector point)
{
	t_vector	tmp1;
	t_vector	tmp2;
	int			i;

	tmp1 = ft_vector_from_a_to_b(frustrum.near_point, frustrum.near_normal);
	tmp2 = ft_vector_from_a_to_b(frustrum.near_point, point);
	i = ft_vector_dot_product(tmp1, tmp2) > 0;
	tmp1 = ft_vector_from_a_to_b(frustrum.far_point, frustrum.far_normal);
	tmp2 = ft_vector_from_a_to_b(frustrum.far_point, point);
	i &= ft_vector_dot_product(tmp1, tmp2) > 0;
	tmp1 = ft_vector_from_a_to_b(frustrum.top_point, frustrum.top_normal);
	tmp2 = ft_vector_from_a_to_b(frustrum.top_point, point);
	i &= ft_vector_dot_product(tmp1, tmp2) > 0;
	tmp1 = ft_vector_from_a_to_b(frustrum.bottom_point, frustrum.bottom_normal);
	tmp2 = ft_vector_from_a_to_b(frustrum.bottom_point, point);
	i &= ft_vector_dot_product(tmp1, tmp2) > 0;
	tmp1 = ft_vector_from_a_to_b(frustrum.right_point, frustrum.right_normal);
	tmp2 = ft_vector_from_a_to_b(frustrum.right_point, point);
	i &= ft_vector_dot_product(tmp1, tmp2) > 0;
	tmp1 = ft_vector_from_a_to_b(frustrum.left_point, frustrum.left_normal);
	tmp2 = ft_vector_from_a_to_b(frustrum.left_point, point);
	i &= ft_vector_dot_product(tmp1, tmp2) > 0;
	return (i);
}

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

	if ((out = (t_object3d*)ft_malloc(sizeof(t_object3d))) == NULL)
		return (NULL);
	if (((out->points3d_original = (t_vector*)ft_malloc(sizeof(t_vector) *
			nb_points)) == NULL) || ((out->colors = (int*)ft_malloc(sizeof(int) *
			nb_points)) == NULL) || ((out->points3d = (t_vector*)ft_malloc(sizeof(
			t_vector) * nb_points)) == NULL) || ((out->points2d =
			(t_point*)ft_malloc(sizeof(t_point) * nb_points)) == NULL) ||
			(out->lines = (t_line_ref*)ft_malloc(sizeof(t_line_ref)
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
	static int		mutex = 0;

	data = (t_mlx_data*)ptr;
	clock_gettime(CLOCK_REALTIME, &time);
	tmpwin = data->windows;
	while (tmpwin != NULL)
	{
		f = time.tv_nsec / (1 + 1000000000L / tmpwin->wfps);
		if (mutex == 0 && (f != tmpwin->last_frame || time.tv_sec != tmpwin->last_time.tv_sec))
		{
			mutex = 1;
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
			mutex = 0;
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

int		color_multiply(int color, double mult)
{
	double red;
	double green;
	double blue;
	//double norm;

	red = (double)((color & 0x00FF0000) >> 16);
	green = (double)((color & 0x0000FF00) >> 8);
	blue = (double)(color & 0x000000FF);
	//norm = MAX(red, green);
	//norm = MAX(norm, blue);
	red = MIN(red * mult, 255);
	green = MIN(green * mult, 255);
	blue = MIN(blue * mult, 255);
	return ((color & 0xFF000000) | (((int)red) << 16) | (((int)green) << 8) | (int)blue);
}

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
		if (data->mice.joystick.y)
		{
			tmp = ft_vector(1, 0, 0);
			r = ft_quat_rotation_build(0.01 * -data->mice.joystick.y, tmp);
			q = fdf->camera.object.orientation;
			fdf->camera.object.orientation = ft_quat_multiply(q, r);
			up = 1;
		}
		if (data->mice.joystick.x)
		{
			tmp = ft_vector(0, 1, 0);
			r = ft_quat_rotation_build(0.01 * data->mice.joystick.x, tmp);
			q = fdf->camera.object.orientation;
			fdf->camera.object.orientation = ft_quat_multiply(q, r);
			up = 1;
		}
		if (data->keymap[KEY_Q] || data->keymap[KEY_E])
		{
			tmp = ft_vector(0, 0, 1);
			r = ft_quat_rotation_build(0.05 * (data->keymap[KEY_E] - data->keymap[KEY_Q]), tmp);
			q = fdf->camera.object.orientation;
			fdf->camera.object.orientation = ft_quat_multiply(q, r);
			up = 1;
		}
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
		if (data->keymap[KEY_PAD_0] && (up = 1))
		{
			fdf->camera.object.position = ft_vector(0, 0, 600);
			fdf->camera.object.orientation = ft_quat(1, 0, 0, 0);
			fdf->camera.object.axis_x = ft_vector(1, 0, 0);
			fdf->camera.object.axis_y = ft_vector(0, 1, 0);
			fdf->camera.object.axis_z = ft_vector(0, 0, 1);
			fdf->camera.frustrum = fdf->camera.frustrum_origin;
			win->zoom = 10;
		}
		if (up)
		{
			t_matrix *tmat = NULL;
			q = ft_quat_inverse(fdf->camera.object.orientation);
			if (data->keymap[KEY_Q] || data->keymap[KEY_E] || data->mice.joystick.x || data->mice.joystick.y)
			{
				tmat = ft_quat_rotation_to_matrix(fdf->camera.object.orientation);
				fdf->camera.object.axis_x = ft_matrix_multply_vector(ft_vector(1, 0, 0), tmat);
				fdf->camera.object.axis_y = ft_matrix_multply_vector(ft_vector(0, 1, 0), tmat);
				fdf->camera.object.axis_z = ft_matrix_multply_vector(ft_vector(0, 0, 1), tmat);
				fdf->camera.frustrum.near_point = ft_matrix_multply_vector(fdf->camera.frustrum_origin.near_point, tmat);
				fdf->camera.frustrum.near_normal = ft_matrix_multply_vector(fdf->camera.frustrum_origin.near_normal, tmat);
				fdf->camera.frustrum.far_point = ft_matrix_multply_vector(fdf->camera.frustrum_origin.far_point, tmat);
				fdf->camera.frustrum.far_normal = ft_matrix_multply_vector(fdf->camera.frustrum_origin.far_normal, tmat);
				fdf->camera.frustrum.top_point = ft_matrix_multply_vector(fdf->camera.frustrum_origin.top_point, tmat);
				fdf->camera.frustrum.top_normal = ft_matrix_multply_vector(fdf->camera.frustrum_origin.top_normal, tmat);
				fdf->camera.frustrum.bottom_point = ft_matrix_multply_vector(fdf->camera.frustrum_origin.bottom_point, tmat);
				fdf->camera.frustrum.bottom_normal = ft_matrix_multply_vector(fdf->camera.frustrum_origin.bottom_normal, tmat);
				fdf->camera.frustrum.right_point = ft_matrix_multply_vector(fdf->camera.frustrum_origin.right_point, tmat);
				fdf->camera.frustrum.right_normal = ft_matrix_multply_vector(fdf->camera.frustrum_origin.right_normal, tmat);
				fdf->camera.frustrum.left_point = ft_matrix_multply_vector(fdf->camera.frustrum_origin.left_point, tmat);
				fdf->camera.frustrum.left_normal = ft_matrix_multply_vector(fdf->camera.frustrum_origin.left_normal, tmat);
				ft_matrix_free(tmat);
			}
			tmat = ft_quat_rotation_to_matrix(q);
			pos.y = -1;
			while (++pos.y < fdf->size.y && (pos.x = -1))
				while (++pos.x < fdf->size.x)
				{
					tmp = fdf->map3[pos.y][pos.x];
					tmp = ft_vector_substract(tmp, fdf->camera.object.position);
					tmp = ft_vector_add(tmp, fdf->camera.focal);
					if (ft_is_in_frustrum(fdf->camera.frustrum, tmp))
					{
						tmp = ft_matrix_multply_vector(tmp, tmat);
						tmp = ft_vector_substract(tmp, fdf->camera.focal);
						fdf->map2[pos.y][pos.x] = ft_3d_to_2d(fdf->camera.focal, ft_point(win->size.x / 2, win->size.y / 2), tmp, win->zoom);
						fdf->zbuffer[pos.y][pos.x] = tmp.z;
					}
					else
					{
						fdf->map2[pos.y][pos.x] = ft_point(0x7FFFFFFF, 0x7FFFFFFF);
						fdf->zbuffer[pos.y][pos.x] = -INFINITY;
					}
				}
//
//			tmp = fdf->camera.frustrum_origin.near_point;

//			tmp = ft_vector_add(tmp, fdf->camera.focal);
//			tmp = ft_vector_substract(tmp, fdf->camera.object.position);
//			ft_matrix_multply_vector(&tmp, tmat);
//			tmp = ft_vector_substract(tmp, fdf->camera.focal);

//			fdf->camera.frustrum.near_point = tmp;
//
			ft_matrix_free(tmat);
			pos.y = -1;
			ftx_clear_img(img);
			while (++pos.y < fdf->size.y && (pos.x = -1))
				while (++pos.x < fdf->size.x)
				{
					if (pos.x < fdf->size.x - 1)
						if (fdf->map2[pos.y][pos.x].x != 0x7FFFFFFF && fdf->map2[pos.y][pos.x + 1].x != 0x7FFFFFFF)
							ftx_line(img, fdf->map2[pos.y][pos.x], fdf->map2[pos.y][pos.x + 1], ft_point(color_multiply(fdf->map[pos.y][pos.x][1], 40 / (700 + fdf->zbuffer[pos.y][pos.x])), color_multiply(fdf->map[pos.y][pos.x + 1][1], 40 / (700 + fdf->zbuffer[pos.y][pos.x + 1]))));
					if (pos.y < fdf->size.y - 1)
						if (fdf->map2[pos.y][pos.x].x != 0x7FFFFFFF && fdf->map2[pos.y + 1][pos.x].x != 0x7FFFFFFF)
							ftx_line(img, fdf->map2[pos.y][pos.x], fdf->map2[pos.y + 1][pos.x], ft_point(color_multiply(fdf->map[pos.y][pos.x][1], 40 / (700 + fdf->zbuffer[pos.y][pos.x])), color_multiply(fdf->map[pos.y + 1][pos.x][1], 40 / (700 + fdf->zbuffer[pos.y + 1][pos.x]))));
				}
		}
	}
	img->update = 1;
	return (0);
}

int		fill_info(t_window *win, t_image *img)
{
	void *tmp;

	t_camera	cam = ((t_fdf*)(win->data))->camera;
	t_point		joy = ftx_data(GDX_ACCES)->mice.joystick;

	ftx_clear_img(img);
	ftx_print_str(img, ft_point(1, 1), WHITE, tmp = ft_itoa(win->fps));free(tmp);

	ftx_print_str(img, ft_point(1, 11), WHITE, "pos: ");
	ftx_print_str(img, ft_point(50, 11), WHITE, tmp = ft_itoa(cam.object.position.x)); free(tmp);
	ftx_print_str(img, ft_point(70, 11), WHITE, tmp = ft_itoa(cam.object.position.y)); free(tmp);
	ftx_print_str(img, ft_point(90, 11), WHITE, tmp = ft_itoa(cam.object.position.z)); free(tmp);

	ftx_print_str(img, ft_point(1, 21), WHITE, "joystick: ");
	ftx_print_str(img, ft_point(70, 21), WHITE, tmp = ft_itoa(joy.x)); free(tmp);
	ftx_print_str(img, ft_point(90, 21), WHITE, tmp = ft_itoa(joy.y)); free(tmp);

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
	fdf->zbuffer = (double**)ft_memalloc(sizeof(double*) * size.y);
	i = -1;
	while (++i < size.y)
	{
		fdf->map3[i] = (t_vector*)ft_memalloc(sizeof(t_vector) * size.x);
		fdf->map2[i] = (t_point*)ft_memalloc(sizeof(t_point) * size.x);
		fdf->zbuffer[i] = (double*)ft_memalloc(sizeof(double) * size.x);
		j = -1;
		while (++j < size.x)
			fdf->map3[i][j] = (t_vector){j, i, map[i][j][0]};
	}
	fdf->camera.object.position = ft_vector(0, 0, 0);
	fdf->camera.object.orientation = ft_quat(1, 0, 0, 0);
	fdf->camera.object.axis_x = ft_vector(1, 0, 0);
	fdf->camera.object.axis_y = ft_vector(0, 1, 0);
	fdf->camera.object.axis_z = ft_vector(0, 0, 1);
	fdf->camera.focal = ft_vector(0, 0, 700);
	fdf->camera.frustrum_origin = ft_frustrum(ft_point(-200, -150), ft_point(200, 150), ft_point(1, 1500), fdf->camera.focal);
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
			map[i.y][i.x][1] = ft_atoi_extended(ft_strchr(tmp, ',') + 1);
		else
			map[i.y][i.x][1] = 0x00FFFF;
		while ((tmp = ft_strnw(tmp))[0] != 0 && !(0 * ++i.x))
		{
			map[i.y][i.x][0] = ft_atoi(tmp);
			if (ft_strchr(tmp, ',') != NULL &&
				ft_strchr(tmp, ',') < ft_strnw(tmp))
				map[i.y][i.x][1] = ft_atoi_extended(ft_strchr(tmp, ',') + 1);
			else
				map[i.y][i.x][1] = 0x00FFFF;
		}
		free(line);
	}
	return (map);
}
//*
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
//*/
/*
int main()
{
	t_frustrum	frustrum = ft_frustrum(ft_point(-50,-50), ft_point(50, 50), ft_point(1,500), ft_vector(0, 0, 700));
	t_vector	point = ft_vector(49, 49, 1.9);
	t_vector	tmp;
	tmp = frustrum.near_point;
	printf("frustrum.near_point: %lf %lf %lf\n", tmp.x, tmp.y, tmp.z);
	tmp = frustrum.near_normal;
	printf("frustrum.near_normal: %lf %lf %lf\n", tmp.x, tmp.y, tmp.z);
	tmp = frustrum.far_point;
	printf("frustrum.far_point: %lf %lf %lf\n", tmp.x, tmp.y, tmp.z);
	tmp = frustrum.far_normal;
	printf("frustrum.far_normal: %lf %lf %lf\n", tmp.x, tmp.y, tmp.z);
	tmp = frustrum.top_point;
	printf("frustrum.top_point: %lf %lf %lf\n", tmp.x, tmp.y, tmp.z);
	tmp = frustrum.top_normal;
	printf("frustrum.top_normal: %lf %lf %lf\n", tmp.x, tmp.y, tmp.z);
	tmp = frustrum.bottom_point;
	printf("frustrum.bottom_point: %lf %lf %lf\n", tmp.x, tmp.y, tmp.z);
	tmp = frustrum.bottom_normal;
	printf("frustrum.bottom_normal: %lf %lf %lf\n", tmp.x, tmp.y, tmp.z);
	tmp = frustrum.right_point;
	printf("frustrum.right_point: %lf %lf %lf\n", tmp.x, tmp.y, tmp.z);
	tmp = frustrum.right_normal;
	printf("frustrum.right_normal: %lf %lf %lf\n", tmp.x, tmp.y, tmp.z);
	tmp = frustrum.left_point;
	printf("frustrum.left_point: %lf %lf %lf\n", tmp.x, tmp.y, tmp.z);
	tmp = frustrum.left_normal;
	printf("frustrum.left_normal: %lf %lf %lf\n", tmp.x, tmp.y, tmp.z);
	(void)ft_is_in_frustrum(frustrum, point);
}
//*/
/*
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
*/
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
