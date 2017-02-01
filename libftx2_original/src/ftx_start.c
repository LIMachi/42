/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 09:37:48 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/07 13:59:10 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <mlx.h>
#include <libftx.h>

static int	sf_tick(void *data)
{
	int			i;
	t_key_data	*keymap;
	t_mice		*mice;

	++((t_ftx_data*)data)->tick;
	keymap = ((t_ftx_data*)data)->keymap;
	i = -1;
	while (++i < KEYMAP_SIZE)
		if (keymap[i]->callback != NULL)
			keymap[i]->callback(i, keymap[i]->status, keymap[i]->data);
	return (((t_ftx_data*)data)->tick);
}

void		ftx_start(void)
{
	t_ftx_data	*data;

	if ((data = ftx_data())->mlx == NULL)
		return ;
	mlx_loop_hook(data->mlx, &sf_tick, (void*)data);
	mlx_do_key_autorepeatoff(data->mlx);
	mlx_loop(data->mlx);
}
