/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_new_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 09:21:21 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/21 17:20:29 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <mlx.h>
#include <libftx.h>

t_image	*ftx_new_image(t_point size)
{
	t_image	*img;
	void	*mlx;

	if ((img = (t_image*)ft_memalloc(sizeof(t_image))) == NULL)
		return (NULL);
	img->size = size;
	if (!((mlx = ftx_data()->mlx) != NULL &&
		(img->img = mlx_new_image(mlx, size.x, size.y)) != NULL &&
		(img->data = (int *)mlx_get_data_addr(img->img,
		&img->bpp, &img->size_line, &img->endian)) != NULL))
	{
		if (img->img)
			mlx_destroy_image(mlx, img->img);
		ft_memdel((void**)img);
	}
	return (img);
}
