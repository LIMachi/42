/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 09:37:48 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/17 14:32:23 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftx.h>
#include <stdio.h>

#if OS == MACINTOCH

static int	sf_tick(void *data)
{
	printf("sf_tick\n");
	return (++((t_ftx_data*)data)->tick);
}

#else

static int	sf_tick(void *data)
{
	printf("sf_tick\n");
	return (++((t_ftx_data*)data)->tick);
}

#endif

void		ftx_start(void)
{
	t_ftx_data	*data;

	if ((data = ftx_data())->mlx == NULL)
		return ;
	write(1, "plop 1\n", 7);
	mlx_loop_hook(data->mlx, &sf_tick, (void*)data);
	write(1, "plop 2\n", 7);
	mlx_loop(data->mlx);
}
