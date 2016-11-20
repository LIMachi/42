/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 09:37:48 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/19 11:43:30 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftx.h>
#include <stdio.h>

extern int mlx_flush_event(void *mlx);

#if OS == MACINTOCH

static int	sf_tick(void *data)
{
	mlx_flush_event(((t_ftx_data*)data)->mlx);
	mlx_do_sync(((t_ftx_data*)data)->mlx);
	return (++((t_ftx_data*)data)->tick);
}

#else

static int	sf_tick(void *data)
{
	mlx_flush_event(((t_ftx_data*)data)->mlx);
	mlx_do_sync(((t_ftx_data*)data)->mlx);
	return (++((t_ftx_data*)data)->tick);
}

#endif

void		ftx_start(void)
{
	t_ftx_data	*data;

	if ((data = ftx_data())->mlx == NULL)
		return ;
	mlx_loop_hook(data->mlx, &sf_tick, (void*)data);
	mlx_loop(data->mlx);
}