/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_free_image.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 09:16:55 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/21 17:20:00 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <mlx.h>
#include <libftx.h>

int		ftx_free_image(t_image *img)
{
	void	*mlx;

	if ((mlx = ftx_data()->mlx) == NULL)
		return (-1);
	if (img == NULL)
		return (1);
	if (img->img)
		mlx_destroy_image(mlx, img->img);
	free(img);
	return (0);
}
