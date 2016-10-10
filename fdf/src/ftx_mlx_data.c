/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_mlx_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/15 09:19:22 by hmartzol          #+#    #+#             */
/*   Updated: 2016/07/15 09:23:35 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftx.h>

t_mlx_data	*ftx_data(int flag)
{
	static t_mlx_data *intern = NULL;

	if (flag & GDX_NEW)
	{
		if (intern != NULL)
			return (NULL);
		else
			intern = (t_mlx_data *)malloc(sizeof(t_mlx_data));
	}
	if (flag & GDX_FREE && intern != NULL)
		ft_memdel((void**)&intern);
	return (intern);
}

void		init_mlx_data(void)
{
	t_mlx_data	*data;

	data = ftx_data(GDX_ACCES);
	ft_bzero((void*)data->keymap, sizeof(int) * KEYMAPSIZE);
	ft_bzero((void*)data->mice.map, sizeof(int) * 10);
	data->mlx = mlx_init();
	data->windows = NULL;
	data->focused_window = 0;
	data->update = 0;
	mlx_do_key_autorepeatoff(data->mlx);
}
