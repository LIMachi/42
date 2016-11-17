/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_new_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 08:28:55 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/17 09:36:33 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftx.h>

t_window	*ftx_new_window(const t_point size, const char *name,
							const uint64_t *id)
{
	t_window	*window;
	void		*mlx;

	if ((window = (t_window*)ft_memalloc(sizeof(t_window))) == NULL)
		return (NULL);
	if ((mlx = ftx_data()->mlx) != NULL &&
			(window->win = mlx_new_window(mlx, size.x, size.y, (char*)name)) != NULL
			&& (window->vbuffer = ftx_new_image(size)) != NULL)
	{
		window->size = size;
		mlx_expose_hook(window->win , &ftx_refresh_window, window);
		ft_2lstadd(&ftx_data()->windows, ft_2lstnew(id, window, 0));
	}
	else
	{
		(void)(window->win && mlx_destroy_window(mlx, window->win));
		(void)(window->vbuffer && !ftx_free_image(window->vbuffer));
		ft_memdel((void**)window);
	}
	return (window);
}
