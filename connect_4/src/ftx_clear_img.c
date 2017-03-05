/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_clear_img.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/27 17:26:25 by hmartzol          #+#    #+#             */
/*   Updated: 2017/03/02 12:52:27 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <connect_4.h>

void	ftx_clear_img(t_mlx mlx)
{
	ft_bzero(mlx.data, sizeof(char) * mlx.sl * mlx.win_size.y);
}
