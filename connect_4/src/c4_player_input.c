/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c4_player_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/27 14:03:49 by hmartzol          #+#    #+#             */
/*   Updated: 2016/02/28 21:42:02 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <connect_4.h>

static int	sf_player_input(t_mlx mlx)
{
	static int	s = 0;
	t_point		t;
	int			i;

	t.x = mlx.win_size.x / 2 - mlx.grid_size.x * 20 - 10;
	t.y = mlx.grid_size.x * 40 + 20;
	if (s && !mlx.micemap[2] && mlx.micemap[0] > t.x
			&& mlx.micemap[0] < t.x + t.y)
	{
		i = 0;
		t.y = 0;
		while (!t.y && ++i <= mlx.grid_size.x)
		{
			t.x = mlx.win_size.x / 2 - mlx.grid_size.x * 20 + (i - 1) * 40 + 20;
			t.y = i * (mlx.micemap[0] > t.x - 18 && mlx.micemap[0] < t.x + 18);
		}
		s = 0;
		return (t.y);
	}
	s = mlx.micemap[2];
	return (0);
}

int			c4_player_input(t_mlx mlx)
{
	int		r;
	char	buff[BUFF_SIZE];

	if (!mlx.mode)
	{
		r = 0;
		while (r < 1 || r > mlx.grid_size.x || mlx.grid[0][r - 1])
		{
			ft_putstr("Enter a row number to put your stone (1 to ");
			ft_putnbr(mlx.grid_size.x);
			write(1, ")\n", 2);
			r = read(0, buff, BUFF_SIZE);
			buff[r - 1] = 0;
			r = ft_atoi(buff);
		}
		return (r);
	}
	else
		return (sf_player_input(mlx));
}
