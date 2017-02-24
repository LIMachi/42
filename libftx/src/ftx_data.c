/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/15 09:19:22 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/08 19:00:07 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftx.h>

t_ftx_data	*ftx_data(int flag)
{
	static t_ftx_data *intern = NULL;

	if (flag & GDX_NEW)
	{
		if (intern != NULL)
			return (NULL);
		else
			intern = (t_ftx_data *)ft_malloc(sizeof(t_ftx_data));
	}
	if (flag & GDX_FREE && intern != NULL)
		ft_memdel((void**)&intern);
	return (intern);
}

t_ftx_data	*init_mlx_data(void)
{
	t_ftx_data	*data;

	if ((data = ftx_data(GDX_ACCES)) == NULL)
		return (NULL);
	ft_bzero((void*)data->keymap, sizeof(int) * KEYMAPSIZE);
	ft_bzero((void*)data->mice.map, sizeof(int) * 10);
	if ((data->mlx = mlx_init()) == NULL)
		return (ftx_data(GDX_FREE));
	data->windows = NULL;
	data->focused_window = 0;
	data->update = 0;
	mlx_do_key_autorepeatoff(data->mlx);
	return (data);
}
