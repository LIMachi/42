/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_resize_window.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 16:28:18 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/05 16:55:02 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftx.h>

/*
** this function is named "ftx_resize_window", but it will actually destroy
** and rebuild the targeted window
*/

t_window	*ftx_resize_window(t_window *win, const t_point size)
{
	t_window	*tmp_win;

	if (size.x <= 0 || size.y <= 0 || (size.x == win->size.x && size.y == win->size.y))
		return (win);
	if ((tmp_win = ftx_new_window(size, (const char *)win->name, NULL)) == NULL)
		return (NULL);
	if (ftx_data()->focused_window == win)
		ftx_data()->focused_window = tmp_win;
	ftx_put_img_to_img(tmp_win->vbuffer, ft_point(0, 0), win->vbuffer, NOMASK);
	ftx_free_window(win);
	return (tmp_win);
}
