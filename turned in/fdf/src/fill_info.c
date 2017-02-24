/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 16:24:49 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/02 08:56:18 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftx.h>

int		fill_info(t_window *win, t_image *img)
{
	void		*tmp;
	t_camera	cam;
	t_point		joy;

	cam = ((t_fdf*)(win->data))->camera;
	joy = ftx_data(GDX_ACCES)->mice.joystick;
	ftx_clear_img(img);
	ftx_print_str(img, ft_point(1, 1), WHITE, tmp = ft_itoa(win->fps));
	ft_free(tmp);
	ftx_print_str(img, ft_point(1, 11), WHITE, "pos: ");
	ftx_print_str(img, ft_point(50, 11), WHITE,
					tmp = ft_itoa(cam.object.position.x));
	ft_free(tmp);
	ftx_print_str(img, ft_point(70, 11), WHITE,
					tmp = ft_itoa(cam.object.position.y));
	ft_free(tmp);
	ftx_print_str(img, ft_point(90, 11), WHITE,
					tmp = ft_itoa(cam.object.position.z));
	ft_free(tmp);
	ftx_print_str(img, ft_point(1, 21), WHITE, "joystick: ");
	ftx_print_str(img, ft_point(70, 21), WHITE, tmp = ft_itoa(joy.x));
	ft_free(tmp);
	ftx_print_str(img, ft_point(90, 21), WHITE, tmp = ft_itoa(joy.y));
	ft_free(tmp);
	return (!(img->update = 1));
}
