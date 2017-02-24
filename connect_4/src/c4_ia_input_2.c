/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c4_ia_input_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgerboui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/28 18:20:43 by tgerboui          #+#    #+#             */
/*   Updated: 2016/02/28 21:30:21 by tgerboui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <connect_4.h>

int	check_h(int **grid, int player, t_point size, t_point t)
{
	int		temp_x;
	int		score;
	int		mul;

	temp_x = t.x;
	mul = 10;
	score = 0;
	while (++temp_x < size.x)
	{
		if (grid[t.y][temp_x] == player)
			score = mul;
		else
			break ;
		mul *= 10;
	}
	temp_x = t.x;
	while (--temp_x >= 0)
	{
		if (grid[t.y][temp_x] == player)
			score = mul;
		else
			break ;
		mul *= 10;
	}
	return (score);
}

int	verif_h(int **grid, int player, t_point size, t_point t)
{
	int		temp_x;
	int		free_case;

	temp_x = t.x;
	free_case = 0;
	while (++temp_x < size.x)
	{
		if (grid[t.y][temp_x] == player || grid[t.y][temp_x] == 0)
			free_case += 1;
		else
			break ;
	}
	temp_x = t.x;
	while (--temp_x >= 0)
	{
		if (grid[t.y][temp_x] == player || grid[t.y][temp_x] == 0)
			free_case += 1;
		else
			break ;
	}
	return (free_case >= 3 ? 1 : 0);
}

int	check_v(int **grid, int player, t_point size, t_point t)
{
	int		temp_y;
	int		score;
	int		mul;

	temp_y = t.y;
	mul = 10;
	score = 0;
	while (++temp_y < size.y)
	{
		if (grid[temp_y][t.x] == player)
			score = mul;
		else
			break ;
		mul *= 10;
	}
	return (score);
}

int	verif_v(int **grid, int player, t_point size, t_point t)
{
	int		temp_y;
	int		free_case;

	temp_y = t.y;
	free_case = 0;
	while (++temp_y < size.y)
	{
		if (grid[temp_y][t.x] == player || grid[temp_y][t.x] == 0)
			free_case += 1;
		else
			break ;
	}
	temp_y = t.y;
	while (--temp_y >= 0)
	{
		if (grid[temp_y][t.x] == player || grid[temp_y][t.x] == 0)
			free_case += 1;
		else
			break ;
	}
	return (free_case >= 3 ? 1 : 0);
}

int	verif_d_2(int **grid, int player, t_point size, t_point t)
{
	int		temp_x;
	int		temp_y;
	int		free_case;

	temp_x = t.x;
	temp_y = t.y;
	free_case = 0;
	while (++temp_x < size.x && --temp_y >= 0)
	{
		if (grid[temp_y][temp_x] == player || grid[temp_y][temp_x] == 0)
			free_case += 1;
		else
			break ;
	}
	temp_x = t.x;
	temp_y = t.y;
	while (--temp_x >= 0 && ++temp_y < size.y)
	{
		if (grid[temp_y][temp_x] == player || grid[temp_y][temp_x] == 0)
			free_case += 1;
		else
			break ;
	}
	return (free_case >= 3 ? 1 : 0);
}
