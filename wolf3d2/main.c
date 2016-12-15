/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 16:49:56 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/02 19:17:19 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <wolf3d.h>
#include <stdio.h>

#define SQUARE 50

typedef struct	s_vector2
{
	double	x;
	double	y;
}				t_vector2;

typedef double	t_mat2[2][2];

typedef struct	s_player
{
	t_vector2	pos;
	double		dir;
	double		fov;
	double		speed;
	double		view_limit;
}				t_player;

typedef struct	s_raycasting_data
{
	t_vector2	ray_dir;
	t_point		map_pos;
	t_vector2	side_dis;
	t_vector2	delta;
	t_point		sign_step;
	double		cam;
}				t_raycasting_data;

typedef struct	s_map
{
	t_point	size;
	char	**map;
}				t_map;

t_player	*player(void)
{
	static t_player	player = {.pos = {1, 1},
								.dir = 0.0,
								.fov = 90 * M_PI_180,
								.speed = 1.0,
								.view_limit = 2};

	return (&player);
}

t_map		*map(void)
{
	static t_map	map = {.size = {0, 0}, .map = NULL};

	return (&map);
}

t_point	sf_dda(t_raycasting_data *rcd, const t_player *p, const t_map *m)
{
	int		side;
	t_point	out;

	side = 0;
	while (rcd->map_pos.y >= 0 && rcd->map_pos.y < m->size.y &&
			rcd->map_pos.x >= 0 && rcd->map_pos.x < m->size.x &&
			!m->map[rcd->map_pos.y][rcd->map_pos.x])
		if (rcd->side_dis.x < rcd->side_dis.y)
		{
			rcd->side_dis.x += rcd->delta.x;
			rcd->map_pos.x += rcd->sign_step.x;
			side = 0;
		}
		else
		{
			rcd->side_dis.y += rcd->delta.y;
			rcd->map_pos.y += rcd->sign_step.y;
			side = 1;
		}
	(void)side;
	(void)p;
//	if (side)
//		rcd->map_pos.y -= rcd->sign_step.y;
//	else
//		rcd->map_pos.x -= rcd->sign_step.x;
	out.x = rcd->map_pos.x * SQUARE + SQUARE / 2;
	out.y = rcd->map_pos.y * SQUARE + SQUARE / 2;
	return (out);
}

t_point	dda(t_raycasting_data *rcd, const t_player *p, const int x,
			const int screen_width)
{
	double		angle;

	angle = (x - screen_width / 2.0) * (p->fov / screen_width);
	rcd->ray_dir.x = cos(p->dir - angle);
	rcd->ray_dir.y = sin(p->dir - angle);
	rcd->map_pos = ft_point(p->pos.x, p->pos.y);
	rcd->delta.x = sqrt((rcd->ray_dir.y * rcd->ray_dir.y) /
							(rcd->ray_dir.x * rcd->ray_dir.x));
	rcd->delta.y = sqrt((rcd->ray_dir.x * rcd->ray_dir.x) /
							(rcd->ray_dir.y * rcd->ray_dir.y));
//	return (ft_point(
//		p->pos.x * SQUARE + rcd->delta.x * SQUARE,
//		p->pos.y * SQUARE + rcd->delta.y * SQUARE
//	));
	if (rcd->ray_dir.x < 0.0)
		(void)((rcd->sign_step.x = -1) +
		(rcd->side_dis.x = (rcd->map_pos.x - p->pos.x)/*(p->pos.x - rcd->map_pos.x)*/ * rcd->delta.x));
	else
		(void)((rcd->sign_step.x = 1) +
		(rcd->side_dis.x = (rcd->map_pos.x + 1.0 - p->pos.x) * rcd->delta.x));
	if (rcd->ray_dir.x < 0.0)
		(void)((rcd->sign_step.y = 1) +
		(rcd->side_dis.y = (rcd->map_pos.y - p->pos.y)/*(p->pos.y - rcd->map_pos.y)*/ * rcd->delta.y));
	else
		(void)((rcd->sign_step.y = -1) +
		(rcd->side_dis.y = (rcd->map_pos.y + 1.0 - p->pos.y) * rcd->delta.y));
//	return (ft_point(rcd->side_dis.x , rcd->side_dis.y ));
	return (sf_dda(rcd, p, map()));
}

void	print(t_image *img)
{
	int 				x;
	int 				y;
	int					i;
	t_raycasting_data	rcd;

	y = -1;
	ftx_fill_image(img, 0, 1.0);
	while (++y < map()->size.y && (x = -1))
		while (++x < map()->size.x)
			if (map()->map[y][x] && (i = -1))
				while (++i < SQUARE)
					ftx_vertical_line(img, ft_point(x * SQUARE + i, y * SQUARE),
						ft_point(x * SQUARE + i, (y + 1) * SQUARE - 1),
						ft_point(CIAN, CIAN));
	i = -1;
	while (++i < 500)
		ftx_line(img, ft_point(player()->pos.x * SQUARE, player()->pos.y * SQUARE),
			dda(&rcd, player(), i, 500), ft_point(GREEN, GRAY));
	ftx_line(img, ft_point(player()->pos.x * SQUARE, player()->pos.y * SQUARE),
		ft_point(player()->pos.x * SQUARE + player()->speed * SQUARE *
		cos(player()->dir), player()->pos.y * SQUARE + player()->speed *
		SQUARE * sin(player()->dir)), ft_point(RED, RED));
	ftx_put_selection_square(img, ft_point(player()->pos.x * SQUARE - SQUARE /
		10, player()->pos.y * SQUARE - SQUARE / 10), ft_point(player()->pos.x *
		SQUARE + SQUARE / 10, player()->pos.y * SQUARE + SQUARE / 10), YELLOW);
}





int		call_exit(int key, int status, void *data)
{
	(void)data;
	if (key == KEY_EXIT && status == FTX_KEY_STATUS_PRESSED)
		exit(0);
	return (0);
}

int		sf_call_move(t_window *win, int up)
{
	if (player()->pos.x < 0.0)
		player()->pos.x = 0.0;
	if (player()->pos.x > map()->size.x - 1)
		player()->pos.x = map()->size.x - 1;
	if (player()->pos.y < 0.0)
		player()->pos.y = 0.0;
	if (player()->pos.y > map()->size.y - 1)
		player()->pos.y = map()->size.y - 1;
	if (up)
	{
		print(win->vbuffer);
		ftx_refresh_window(win);
	}
	return (0);
}

int		call_move(int key, int status, void *data)
{
	int		up;

	up = 0;
	if (key == KEY_W && status == FTX_KEY_STATUS_PRESSED && (up = 1))
	{
		player()->pos.x += cos(player()->dir) * player()->speed;
		player()->pos.y += sin(player()->dir) * player()->speed;
	}
	if (key == KEY_D && status == FTX_KEY_STATUS_PRESSED && (up = 1))
	{
		player()->pos.x += cos(player()->dir + M_PI_2) * player()->speed;
		player()->pos.y += sin(player()->dir + M_PI_2) * player()->speed;
	}
	if (key == KEY_S && status == FTX_KEY_STATUS_PRESSED && (up = 1))
	{
		player()->pos.x += cos(player()->dir + M_PI) * player()->speed;
		player()->pos.y += sin(player()->dir + M_PI) * player()->speed;
	}
	if (key == KEY_A && status == FTX_KEY_STATUS_PRESSED && (up = 1))
	{
		player()->pos.x += cos(player()->dir + M_PI + M_PI_2) * player()->speed;
		player()->pos.y += sin(player()->dir + M_PI + M_PI_2) * player()->speed;
	}
	return (sf_call_move((t_window*)data, up));
}

int		call_turn(int key, int status, void *data)
{
	int		up;

	up = 0;
	if (key == KEY_UP && status == FTX_KEY_STATUS_PRESSED && (up = 1))
		player()->speed += 1.0 / SQUARE;
	if (key == KEY_RIGHT && status == FTX_KEY_STATUS_PRESSED && (up = 1))
		player()->dir += player()->fov / 8;
	if (key == KEY_DOWN && status == FTX_KEY_STATUS_PRESSED && (up = 1))
		player()->speed -= 1.0 / SQUARE;
	if (key == KEY_LEFT && status == FTX_KEY_STATUS_PRESSED && (up = 1))
		player()->dir -= player()->fov / 8;
	if (up)
	{
		print(((t_window*)data)->vbuffer);
		ftx_refresh_window((t_window*)data);
	}
	return (0);
}


void	wolf3d(void)
{
	t_window		*win;

	if ((win = ftx_new_window(ft_point(10 * SQUARE, 10 * SQUARE), "wolf",
								(const uint64_t *)"wolf")) == NULL)
		return ;
	ftx_key_hook(KEY_EXIT, &call_exit, win);
	ftx_key_hook(KEY_W, &call_move, win);
	ftx_key_hook(KEY_A, &call_move, win);
	ftx_key_hook(KEY_S, &call_move, win);
	ftx_key_hook(KEY_D, &call_move, win);
	ftx_key_hook(KEY_UP, &call_turn, win);
	ftx_key_hook(KEY_RIGHT, &call_turn, win);
	ftx_key_hook(KEY_DOWN, &call_turn, win);
	ftx_key_hook(KEY_LEFT, &call_turn, win);
	print(win->vbuffer);
	ftx_refresh_window(win);
	ftx_start();
}

int		main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	ft_init(env);
	map()->map = (char**)ft_taballoc(10, 10, sizeof(char));
	map()->size = (t_point){10, 10};
	for (int y = 0; y < 10; ++y)
		for (int x = 0; x < 10; ++x)
			map()->map[y][x] = ((x == 0) || (y == 0) || (x == 9) || (y == 9));
	player()->pos = (t_vector2){5.0, 2.0};
	wolf3d();
	return (0);
}
