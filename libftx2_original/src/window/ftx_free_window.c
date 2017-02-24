/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_free_window.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 08:35:40 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/05 16:54:06 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <mlx.h>
#include <libftx.h>

int			ftx_free_window(t_window *win)
{
	void		*mlx;
	t_2list		*node;

	if ((mlx = ftx_data()->mlx) == NULL)
		return (-1);
	if ((node = ft_2lsearchcontent(ftx_data()->windows, win)) == NULL)
		return (1);
	if (ftx_data()->focused_window == win)
		ftx_data()->focused_window == NULL;
	(void)(win->win && mlx_destroy_window(mlx, win->win));
	(void)(win->vbuffer && ftx_free_image(win->vbuffer));
	(void)ft_free(win->name);
	ft_free(ft_object_free_node((t_object*)node));
	return (0);
}
