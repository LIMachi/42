/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_free_window.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 08:35:40 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/21 17:21:30 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <mlx.h>
#include <libftx.h>

int			ftx_free_window(const uint64_t *id)
{
	void		*mlx;
	t_2list		*node;
	t_window	*win;

	if ((mlx = ftx_data()->mlx) == NULL)
		return (-1);
	if ((node = ft_2lstsearchid(id, ftx_data()->windows)) == NULL)
		return (1);
	win = (t_window*)node->data;
	(void)(win->win && mlx_destroy_window(mlx, win->win));
	(void)(win->vbuffer && ftx_free_image(win->vbuffer));
	ft_free(ft_object_free_node((t_object*)node));
	return (0);
}
