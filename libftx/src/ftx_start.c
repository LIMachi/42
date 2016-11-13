/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 17:15:31 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/08 21:00:08 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftx.h>

void	ftx_start(void)
{
	t_ftx_data	*data;

	if ((data = ftx_data(GDX_ACCES)) == NULL)
		return ;
	mlx_loop_hook(data->mlx, ftx_update, (void*)data);
	mlx_loop(data->mlx);
}
