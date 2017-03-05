/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c4_put_stone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/27 13:47:02 by hmartzol          #+#    #+#             */
/*   Updated: 2017/03/02 12:52:23 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <connect_4.h>

int		c4_put_stone(int **grid, int column, int player, t_point size)
{
	int	i;

	i = 0;
	if (grid[0][column])
		return (-1);
	while (i < size.y - 1 && !grid[i + 1][column])
		++i;
	grid[i][column] = player;
	return (0);
}
