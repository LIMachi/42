/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c4_ia_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgerboui <tgerboui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/27 12:50:26 by tgerboui          #+#    #+#             */
/*   Updated: 2017/03/02 12:52:12 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <connect_4.h>
#include <stdio.h>

static int	check_d_2(int **grid, int player, t_point size, t_point t)
{
	int		temp_x;
	int		temp_y;
	int		score;
	int		mul;

	temp_x = t.x;
	temp_y = t.y;
	mul = 10;
	score = 0;
	while (++temp_x < size.x && --temp_y >= 0
			&& grid[temp_y][temp_x] == player)
	{
		score = mul;
		mul *= 10;
	}
	temp_x = t.x;
	temp_y = t.y;
	while (--temp_x >= 0 && ++temp_y < size.y
			&& grid[temp_y][temp_x] == player)
	{
		score = mul;
		mul *= 10;
	}
	return (score);
}

static int	check_d(int **grid, int player, t_point size, t_point t)
{
	int		temp_x;
	int		temp_y;
	int		score;
	int		mul;

	temp_x = t.x;
	temp_y = t.y;
	mul = 10;
	score = 0;
	while (++temp_x < size.x && ++temp_y < size.y
			&& grid[temp_y][temp_x] == player)
	{
		score = mul;
		mul *= 10;
	}
	temp_x = t.x;
	temp_y = t.y;
	while (--temp_x >= 0 && --temp_y >= 0
			&& grid[temp_y][temp_x] == player)
	{
		score = mul;
		mul *= 10;
	}
	return (score);
}

static int	verif_d(int **grid, int player, t_point size, t_point t)
{
	int		temp_x;
	int		temp_y;
	int		free_case;

	temp_x = t.x;
	temp_y = t.y;
	free_case = 0;
	while (++temp_x < size.x && ++temp_y < size.y)
	{
		if (grid[temp_y][temp_x] == player || grid[temp_y][temp_x] == 0)
			free_case += 1;
		else
			break ;
	}
	temp_x = t.x;
	temp_y = t.y;
	while (--temp_x >= 0 && --temp_y >= 0)
	{
		if (grid[temp_y][temp_x] == player || grid[temp_y][temp_x] == 0)
			free_case += 1;
		else
			break ;
	}
	return (free_case >= 3 ? 1 : 0);
}

int			check(int **grid, int player, t_point size, t_point t)
{
	int		score;

	score = 0;
	if (verif_h(grid, player, size, t) == 1)
		score += check_h(grid, player, size, t);
	if (verif_v(grid, player, size, t) == 1)
		score += check_v(grid, player, size, t);
	if (verif_d(grid, player, size, t) == 1)
		score += check_d(grid, player, size, t);
	if (verif_d_2(grid, player, size, t) == 1)
		score += check_d_2(grid, player, size, t);
	if (t.x == size.x / 2)
		score += 2;
	score += 1;
	return (score);
}

int			c4_ia_input(int **grid, int player, t_point size)
{
	t_point	t;
	int		best_x;
	int		score;
	int		score_temp;

	t.y = -1;
	score = 0;
	t.x = size.x;
	best_x = size.x / 2 + 1;
	while (!(t.y = 0) && --t.x >= 0)
		if (grid[0][t.x] == 0)
		{
			while (t.y < size.y - 1 && grid[t.y + 1][t.x] == 0)
				t.y++;
			score_temp = (check(grid, player, size, t)
					+ (check(grid, 1, size, t)) / 2);
			if (t.y - 1 >= 0 && score < 1000)
				score_temp -= check(grid, 1, size, ft_point(t.x, t.y - 1))
					>= 500 ? 500 : 0;
			if (score_temp >= score && grid[t.y][t.x] == 0
					&& (best_x = t.x + 1))
				score = score_temp;
		}
	return (best_x);
}
