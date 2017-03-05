/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c4_check_grid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/27 13:53:17 by hmartzol          #+#    #+#             */
/*   Updated: 2017/03/02 12:52:06 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <connect_4.h>

static int	check_grid2(int **grid, t_point size, t_point pos)
{
	int	i;
	int	countr;
	int countl;

	i = 0;
	countr = 1;
	countl = 1;
	while (++i < STONES_TO_CONNECT)
	{
		countr += pos.x + i < size.x && pos.y + i < size.y &&
				grid[pos.y][pos.x] == grid[pos.y + i][pos.x + i];
		countl += pos.x + i < size.x && pos.y - i >= 0 &&
				grid[pos.y][pos.x] == grid[pos.y - i][pos.x + i];
	}
	if (countr == STONES_TO_CONNECT || countl == STONES_TO_CONNECT)
		return (grid[pos.y][pos.x]);
	return (0);
}

static int	check_grid1(int **grid, t_point size, t_point pos)
{
	int	i;
	int	counth;
	int	countv;

	i = 0;
	counth = 1;
	countv = 1;
	while (++i < STONES_TO_CONNECT)
	{
		counth += pos.x + i < size.x &&
				grid[pos.y][pos.x] == grid[pos.y][pos.x + i];
		countv += pos.y + i < size.y &&
				grid[pos.y][pos.x] == grid[pos.y + i][pos.x];
	}
	if (counth == STONES_TO_CONNECT || countv == STONES_TO_CONNECT)
		return (grid[pos.y][pos.x]);
	return (check_grid2(grid, size, pos));
}

int			c4_check_grid(int **grid, t_point size)
{
	t_point	t;
	int		empty;
	int		out;

	t.y = -1;
	empty = 0;
	while (++t.y < size.y && (t.x = -1))
		while (++t.x < size.x)
			if (!grid[t.y][t.x])
				++empty;
			else if ((out = check_grid1(grid, size, t)))
				return (out);
	if (!empty)
		return (3);
	return (0);
}
