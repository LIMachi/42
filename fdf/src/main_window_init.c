/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_window_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 16:38:29 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/02 09:46:12 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftx.h>

static void			*sf_memalloc(size_t size)
{
	void	*out;

	if ((out = ft_memalloc(size)) == NULL)
		ftx_error("memalloc failed\n");
	return (out);
}

static t_frustrum	sf_default_frustrum(t_vector focal)
{
	return (ft_frustrum(ft_point(-200, -150),
		ft_point(200, 150), ft_point(1, 1500), focal));
}

static t_fdf		*sf_prepare_fdf(int ***map, t_point size, int i, int j)
{
	t_fdf	*fdf;

	fdf = (t_fdf*)sf_memalloc(sizeof(t_fdf));
	fdf->map = map;
	fdf->size = size;
	fdf->map3 = (t_vector**)sf_memalloc(sizeof(t_vector*) * size.y);
	fdf->map2 = (t_point**)sf_memalloc(sizeof(t_point*) * size.y);
	fdf->zbuffer = (double**)sf_memalloc(sizeof(double*) * size.y);
	i = -1;
	while (++i < size.y && (j = -1))
	{
		fdf->map3[i] = (t_vector*)sf_memalloc(sizeof(t_vector) * size.x);
		fdf->map2[i] = (t_point*)sf_memalloc(sizeof(t_point) * size.x);
		fdf->zbuffer[i] = (double*)sf_memalloc(sizeof(double) * size.x);
		while (++j < size.x)
			fdf->map3[i][j] = (t_vector){j, i, map[i][j][0]};
	}
	fdf->camera.object.position = ft_vector(0, 0, 0);
	fdf->camera.object.orientation = ft_quat(1, 0, 0, 0);
	fdf->camera.object.axis_x = ft_vector(1, 0, 0);
	fdf->camera.object.axis_y = ft_vector(0, 1, 0);
	fdf->camera.object.axis_z = ft_vector(0, 0, 1);
	fdf->camera.focal = ft_vector(0, 0, 700);
	fdf->camera.frustrum_origin = sf_default_frustrum(fdf->camera.focal);
	return (fdf);
}

void				main_window_init(int ***map, t_point size)
{
	t_window	*window;
	t_image		*image;

	window = ftx_new_window(ft_point(1000, 1000), "fdf", 60);
	image = ftx_new_image(ft_point(1000, 1000));
	image->fill_func = fill_fdf;
	ftx_add_image(window, image, 1);
	image = ftx_new_image(ft_point(200, 100));
	image->fill_func = fill_info;
	ftx_add_image(window, image, 2);
	window->up_func = NULL;
	window->data = (void*)sf_prepare_fdf(map, size, -1, -1);
	window->use_code = C_FDF;
	ftx_add_window(window);
	mlx_hook(window->win, 2, (1L << 0), ftx_keypress_hook, window);
	mlx_hook(window->win, 3, (1L << 1), ftx_keyrelease_hook, window);
	mlx_hook(window->win, 4, (1L << 2), ftx_buttonpress_hook, window);
	mlx_hook(window->win, 5, (1L << 3), ftx_buttonrelease_hook, window);
	mlx_hook(window->win, 6, (1L << 6), ftx_motion_hook, window);
}
