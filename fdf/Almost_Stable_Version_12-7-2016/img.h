/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 14:36:32 by hmartzol          #+#    #+#             */
/*   Updated: 2016/06/22 15:07:46 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftx.h>

//void	ft_putpixelimg(void *mlx, t_image *img, t_point pos, int color)

int	color_map[] = {
	0x000000, //0 black
	0xFFFFFF, //1 white
	0xFF0000, //2 red
	0x00FF00, //3 green
	0x0000FF, //4 blue
	0xAAAAAA, //5 light grey
	0x555555, //6 dark grey
};

int	*small_button[8] = {
{7, 7},
{5, 5, 5, 5, 5, 5, 5},
{5, 6, 6, 6, 6, 6, 5},
{5, 6, 6, 6, 6, 6, 5},
{5, 6, 6, 6, 6, 6, 5},
{5, 6, 6, 6, 6, 6, 5},
{5, 6, 6, 6, 6, 6, 5},
{5, 5, 5, 5, 5, 5, 5}
};


t_image	*bmp_to_img(int **bmp, int *color_map, t_mlx_data *data)
{
	t_image *img;
	int		x;
	int		y;

	if (bmp == NULL || *bmp == NULL || color_map == NULL || data == NULL)
		return (NULL);
	if (bmp[0][0] <= 0 || bmp[0][1] <= 0)
		return (NULL);
	if ((img = (t_image*)malloc(sizeof(t_image))) == NULL)
		return (NULL);
	if ((img->ptr = mlx_new_image(data->mlx, bmp[0][0], bmp[0][1])) == NULL)
	{
		free(img);
		return (NULL);
	}
	y = -1;
	while (++y < bmp[0][1] && (x = -1))
		while (++x < bmp[0][0])
			ft_putpixelimg(data->mlx, img, ft_point(x, y), color_map[bmp[y][x]]);
	return (img);
}
