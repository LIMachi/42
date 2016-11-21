/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 09:37:48 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/21 17:19:27 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <mlx.h>
#include <libftx.h>

#if OS == MACINTOCH

static int	sf_tick(void *data)
{
	return (++((t_ftx_data*)data)->tick);
}

#else

static int	sf_tick(void *data)
{
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
