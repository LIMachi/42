/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_create_window.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 18:24:57 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/09 16:59:52 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftx.h>

t_window	*ftx_create_window(char *name, const t_point size,
						const unsigned int fps, t_int_func_undef image_filler)
{
	t_window	*window;
	t_image		*image;

	if ((window = ftx_new_window(size, name, fps)) == NULL ||
			(image = ftx_new_image(size)) == NULL)
		return (ft_free(window));
	image->fill_func = image_filler;
	ftx_add_image(window, image, 0);
	window->up_func = NULL;
	window->data = NULL;
	window->use_code = 0;
	if (ftx_add_window(window) == -1)
		return ((void*)((long)ft_free(image) + (long)ft_free(window)));
	mlx_hook(window->win, 2, (1L << 0), ftx_keypress_hook, window);
	mlx_hook(window->win, 3, (1L << 1), ftx_keyrelease_hook, window);
	mlx_hook(window->win, 4, (1L << 2), ftx_buttonpress_hook, window);
	mlx_hook(window->win, 5, (1L << 3), ftx_buttonrelease_hook, window);
	mlx_hook(window->win, 6, (1L << 6), ftx_motion_hook, window);
	return (window);
}
