/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c4_print_grid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/27 13:49:57 by hmartzol          #+#    #+#             */
/*   Updated: 2017/03/02 12:52:21 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <connect_4.h>

static void	sf_print_grid(t_mlx mlx)
{
	static int	first_run = 1;
	t_pixel		tmp;
	t_point		pos;

	if (first_run)
	{
		tmp.color = 0xFF;
		tmp.pos = ft_point(mlx.win_size.x / 2 - mlx.grid_size.x * 20 - 5,
						mlx.win_size.y / 2 - mlx.grid_size.y * 20 - 5);
		ftx_put_square(mlx, tmp, ft_point(mlx.grid_size.x * 40 + 10,
					mlx.grid_size.y * 40 + 10));
	}
	pos.y = -1;
	while (++pos.y < mlx.grid_size.y && (pos.x = -1))
		while (++pos.x < mlx.grid_size.x)
		{
			tmp.color = (mlx.grid[pos.y][pos.x] == 1) * 0xFFFF00 |
			(mlx.grid[pos.y][pos.x] == 2) * 0xFF0000;
			tmp.pos = ft_point(mlx.win_size.x / 2 - mlx.grid_size.x * 20
						+ pos.x * 40 + 20, mlx.win_size.y / 2 -
						mlx.grid_size.y * 20 + pos.y * 40 + 20);
			if (first_run || tmp.color)
				ftx_put_circle(mlx, tmp, 18, MODE_FILL);
		}
	first_run = 0;
}

static void	sf_print_numbers(int length)
{
	int i;

	i = -1;
	write(1, " \x1b[32m", 6);
	while (++i < length)
	{
		ft_putnbr(i + 1);
		write(1, "  ", (i < 9) + (i < 99));
	}
	write(1, "\n\x1b[0m", 5);
}

static void	sf_print_line(int length)
{
	int i;

	i = -1;
	while (++i < length)
		write(1, "\x1B[34m+--", 8);
	write(1, "+\n", 2);
}

void		c4_print_grid(t_mlx mlx)
{
	t_point	t;

	if (!mlx.mode)
	{
		t.y = -1;
		while ((t.x = -1) && ++t.y < mlx.grid_size.y)
		{
			sf_print_line(mlx.grid_size.x);
			while (++t.x < mlx.grid_size.x)
			{
				write(1, "|", 1);
				if (mlx.grid[t.y][t.x] == 1)
					write(1, "\x1B[33mPL\x1B[34m", 12);
				else if (mlx.grid[t.y][t.x] == 2)
					write(1, "\x1B[31mAI\x1B[34m", 12);
				else
					write(1, "  ", 2);
			}
			write(1, "|\n", 2);
		}
		sf_print_line(mlx.grid_size.x);
		sf_print_numbers(mlx.grid_size.x);
	}
	else
		sf_print_grid(mlx);
}
