/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_new_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 08:28:55 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/17 14:02:37 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftx.h>

#define FTX_DOUBLETAP_TICK 20

static int	sf_call_keydown(int key)
{
	t_key_data	*pkey;

	pkey = &ftx_data()->keymap[key];
	if (pkey->tick - ftx_data()->tick < FTX_DOUBLETAP_TICK)
		pkey->status = FTX_KEY_STATUS_DOUBLED;
	else
		pkey->status = FTX_KEY_STATUS_PRESSED;
	pkey->tick = ftx_data()->tick;
	if (pkey->callback != NULL)
		return (pkey->callback(key, pkey->status, pkey->data));
	return (0);
}

static int	sf_call_keyup(int key)
{
	t_key_data	*pkey;

	pkey = &ftx_data()->keymap[key];
	pkey->status = FTX_KEY_STATUS_RELEASED;
	if (pkey->callback != NULL)
		return (pkey->callback(key, FTX_KEY_STATUS_RELEASED, pkey->data));
	return (0);
}

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
		mlx_hook(window->win, 2, (1L << 0), &sf_call_keydown, NULL);
		mlx_hook(window->win, 3, (1L << 1), &sf_call_keyup, NULL);
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
