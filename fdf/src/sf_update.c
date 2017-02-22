/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sf_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 12:37:40 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/02 13:05:11 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftx.h>

inline static t_matrix	*sf_update0(t_fdf *fdf, int up)
{
	t_quaternion	q;
	t_matrix		*tmat;

	q = ft_quat_inverse(fdf->camera.object.orientation);
	if (up & 1)
	{
		tmat = ft_quat_rotation_to_matrix(NULL, fdf->camera.object.orientation);
		fdf->camera.object.axis_x = ft_matrix_multply_vector(ft_vector(1, 0, 0),
															tmat);
		fdf->camera.object.axis_y = ft_matrix_multply_vector(ft_vector(0, 1, 0),
															tmat);
		fdf->camera.object.axis_z = ft_matrix_multply_vector(ft_vector(0, 0, 1),
															tmat);
		ft_memcpy(&fdf->camera.frustrum, &fdf->camera.frustrum_origin,
												sizeof(t_frustrum));
		ft_matrix_multply_vector_array((t_vector*)(&fdf->camera.frustrum), 12,
										tmat);
		ft_matrix_free(tmat);
	}
	tmat = ft_quat_rotation_to_matrix(NULL, q);
	return (tmat);
}

inline static t_point	sf_update1(int up, t_point pos, t_fdf *fdf,
													t_window *win)
{
	t_vector		tmp;
	t_matrix		*tmat;

	tmat = sf_update0(fdf, up);
	while (++pos.y < fdf->size.y && (pos.x = -1))
		while (++pos.x < fdf->size.x)
		{
			tmp = ft_vector_add(ft_vector_substract(fdf->map3[pos.y][pos.x],
						fdf->camera.object.position), fdf->camera.focal);
			if (ft_is_in_frustrum(fdf->camera.frustrum, tmp))
			{
				tmp = ft_vector_substract(ft_matrix_multply_vector(tmp, tmat),
											fdf->camera.focal);
				fdf->map2[pos.y][pos.x] = ft_3d_to_2d(fdf->camera.focal,
					ft_point(win->size.x / 2, win->size.y / 2), tmp);
				fdf->zbuffer[pos.y][pos.x] = tmp.z;
			}
			else
			{
				fdf->map2[pos.y][pos.x] = ft_point(0x7FFFFFFF, 0);
				fdf->zbuffer[pos.y][pos.x] = -INFINITY;
			}
		}
	ft_matrix_free(tmat);
	return (ft_point(-1, -1));
}

void					sf_update(int up, t_fdf *fdf, t_image *img,
													t_window *win)
{
	t_point			pos;

	pos = sf_update1(up, ft_point(-1, -1), fdf, win);
	ftx_clear_img(img);
	while (++pos.y < fdf->size.y && (pos.x = -1))
		while (++pos.x < fdf->size.x)
		{
			if (pos.x < fdf->size.x - 1)
				if (fdf->map2[pos.y][pos.x].x != 0x7FFFFFFF &&
						fdf->map2[pos.y][pos.x + 1].x != 0x7FFFFFFF)
					ftx_line(img, fdf->map2[pos.y][pos.x],
	fdf->map2[pos.y][pos.x + 1], ft_point(color_multiply(
	fdf->map[pos.y][pos.x][1], 40 / (700 + fdf->zbuffer[pos.y][pos.x])),
	color_multiply(fdf->map[pos.y][pos.x + 1][1], 40 / (700 +
	fdf->zbuffer[pos.y][pos.x + 1]))));
			if (pos.y < fdf->size.y - 1)
				if (fdf->map2[pos.y][pos.x].x != 0x7FFFFFFF &&
					fdf->map2[pos.y + 1][pos.x].x != 0x7FFFFFFF)
					ftx_line(img, fdf->map2[pos.y][pos.x],
	fdf->map2[pos.y + 1][pos.x], ft_point(color_multiply(
	fdf->map[pos.y][pos.x][1], 40 / (700 + fdf->zbuffer[pos.y][pos.x])),
	color_multiply(fdf->map[pos.y + 1][pos.x][1], 40 / (700 +
	fdf->zbuffer[pos.y + 1][pos.x]))));
		}
}
