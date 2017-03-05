/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/27 10:27:52 by hmartzol          #+#    #+#             */
/*   Updated: 2017/03/02 12:52:38 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <connect_4.h>

static int		sf_print_winner(void *param, int code)
{
	t_mlx	mlx;
	char	msg[16];

	mlx = *(t_mlx*)param;
	if (!code)
		return (0);
	if (!mlx.mode)
		c4_clear_screen();
	c4_print_grid(mlx);
	if (code == 3)
		ft_memmove(msg, "It's a draw!", 13);
	else if (code == 2)
		ft_memmove(msg, "The AI win!", 13);
	else if (code == 1)
		ft_memmove(msg, "The player win!", 16);
	if (!mlx.mode)
		ft_putendl(msg);
	else
	{
		ftx_expose(param);
		mlx_string_put(mlx.ptr, mlx.win, mlx.win_size.x / 2 - 60,
				mlx.win_size.y / 2 - 10, 0x00808080, msg);
	}
	mlx.stop[0] = 1;
	return (code);
}

static int		sf_game(void *param)
{
	static int	current = 0;
	int			t;
	t_mlx		mlx;

	mlx = *(t_mlx*)param;
	if (!mlx.mode)
		c4_clear_screen();
	c4_print_grid(mlx);
	if (mlx.mode)
		ftx_expose((void*)&mlx);
	if (mlx.stop[0])
		c4_wait(3);
	if (mlx.keymap[53] || mlx.stop[0])
		ftx_quit(mlx);
	t = 0;
	if (!current)
		current = rand() % 2 + 1;
	if (current == 2)
		c4_put_stone(mlx.grid, c4_ia_input(mlx.grid, 2,
					mlx.grid_size) - (current = 1), 2, mlx.grid_size);
	else if ((t = c4_player_input(mlx)))
		if (!c4_put_stone(mlx.grid, t - 1, 1, mlx.grid_size))
			current = 2;
	return (sf_print_winner(param, c4_check_grid(mlx.grid, mlx.grid_size)));
}

static t_point	sf_get_size(int argc, char **argv, t_mlx mlx)
{
	t_point	out;

	if (argc < 5 || (out.x = ft_atoi(argv[4])) < mlx.grid_size.x * 40 + 40)
		out.x = mlx.grid_size.x * 40 + 40;
	if (argc < 6 || (out.y = ft_atoi(argv[5])) < mlx.grid_size.y * 40 + 40)
		out.y = mlx.grid_size.y * 40 + 40;
	return (out);
}

int				main(int argc, char **argv)
{
	t_mlx	mlx;
	int		win;

	if ((mlx.grid = c4_prepare_grid(argc, argv, &mlx.grid_size)) == NULL)
		return (0);
	mlx.stop = ft_memalloc(sizeof(int));
	srand(time(NULL));
	if ((mlx.mode = argc > 3 && ft_atoi(argv[3])))
	{
		mlx.win_size = sf_get_size(argc, argv, mlx);
		mlx.ptr = mlx_init();
		mlx.win = mlx_new_window(mlx.ptr, mlx.win_size.x, mlx.win_size.y,
					"Puissance 4");
		mlx.img = mlx_new_image(mlx.ptr, mlx.win_size.x, mlx.win_size.y);
		mlx.data = mlx_get_data_addr(mlx.img, &mlx.bpp, &mlx.sl, &mlx.endian);
		ftx_hook_keyinit(&mlx);
		ftx_hook_miceinit(&mlx);
		mlx_loop_hook(mlx.ptr, &sf_game, (void*)&mlx);
		mlx_do_key_autorepeatoff(mlx.ptr);
		mlx_loop(mlx.ptr);
	}
	else
		while (!(win = sf_game((void*)&mlx)))
			;
	return (0);
}
