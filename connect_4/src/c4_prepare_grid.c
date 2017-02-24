/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c4_prepare_grid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/27 14:16:54 by hmartzol          #+#    #+#             */
/*   Updated: 2016/02/27 15:38:12 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <connect_4.h>

int		**c4_prepare_grid(int argc, char **argv, t_point *size)
{
	int		**out;
	t_point	t;

	if (argc < 3)
	{
		ft_putendl("Wrong number of parameters, takes at least 2 parameters \
(width and length of the grid to play on)");
		return (NULL);
	}
	*size = ft_point(ft_atoi(argv[1]), ft_atoi(argv[2]));
	if (size->x < MINIMUM_GRID_WIDTH || size->y < MINIMUM_GRID_HEIGHT)
	{
		ft_putendl("The grid is too small, use bigger width and/or height");
		return (NULL);
	}
	if ((out = (int **)malloc(sizeof(int *) * size->y)) == NULL)
		return (NULL);
	t.y = -1;
	while (++t.y < size->y && (t.x = -1))
		if ((out[t.y] = (int *)malloc(sizeof(int) * size->x)) == NULL)
			return (0);
		else
			while (++t.x < size->x)
				out[t.y][t.x] = 0;
	return (out);
}
