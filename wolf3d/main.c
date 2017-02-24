/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 16:49:56 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/29 07:08:10 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <wolf3d.h>
#include <stdio.h>

#define SPEED 2.0
#define TURN_SPEED (M_PI / 10.0)

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
								.fov = 30 * M_PI / 180.0,
								.speed = 1.0};

	return (&player);
}

t_map		*map(void)
{
	static t_map	map = {.size = {0, 0}, .map = NULL};

	return (&map);
}

inline static void	prepare(t_raycasting_data *rcd, const t_player *p,
							const int x, const int screen_width)
{
	rcd->cam = ((double)x - (double)screen_width / 2.0) * (p->fov / (double)screen_width);
//	cam = 2.0 * (double)x / (double)screen_width - 1.0;
	rcd->map_pos = (t_point){.x = p->pos.x, .y = p->pos.y};
	rcd->ray_dir.x = sin(rcd->cam + p->dir);
	rcd->ray_dir.y = cos(rcd->cam + p->dir);
//	rcd->ray_dir. = p->dir.x + p->scr.x * cam;
//	rcd->ray_dir.y = p->dir.y + p->scr.y * cam;
	rcd->delta.x = sqrt(1 + (rcd->ray_dir.y * rcd->ray_dir.y) / (rcd->ray_dir.x
															* rcd->ray_dir.x));
	rcd->delta.y = sqrt(1 + (rcd->ray_dir.x * rcd->ray_dir.x) / (rcd->ray_dir.y
															* rcd->ray_dir.y));
	if (rcd->ray_dir.x < 0.0)
		(void)((rcd->sign_step.x = -1) +
		(rcd->side_dis.x = (p->pos.x - rcd->map_pos.x) * rcd->delta.x));
	else
		(void)((rcd->sign_step.x = 1) +
		(rcd->side_dis.x = (rcd->map_pos.x + 1.0 - p->pos.x) * rcd->delta.x));
	if (rcd->ray_dir.x < 0.0)
		(void)((rcd->sign_step.y = -1) +
		(rcd->side_dis.y = (p->pos.y - rcd->map_pos.y) * rcd->delta.y));
	else
		(void)((rcd->sign_step.y = 1) +
		(rcd->side_dis.y = (rcd->map_pos.y + 1.0 - p->pos.y) * rcd->delta.y));
}

inline static t_point	dda_side_height(t_raycasting_data *rcd,
					const t_player *p, const t_map *m, const int screen_height)
{
	int	side;

	(void)p;
//	printf("pos: %f, %f\n", p->pos.x, p->pos.y);
	side = rcd->side_dis.y < rcd->side_dis.x;
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
//	printf("\nside: %i\n", side);
//	printf("screen: %i\n", screen_height);
//	printf("collision: %i, %i\n", rcd->map_pos.x, rcd->map_pos.y);
//	printf("player: %f, %f\n", p->pos.x, p->pos.y);
//	printf("step: %i, %i\n", rcd->sign_step.x, rcd->sign_step.y);
//	printf("dir: %f, %f\n", rcd->ray_dir.x, rcd->ray_dir.y);
//	printf("test: %f\n",
//(double)-screen_height / (((double)rcd->map_pos.x -
//(double)p->pos.x + (1.0 - (double)rcd->sign_step.x) / 2.0) / rcd->ray_dir.x)
//);
//	if (side == 1)
//		return ((t_point){.x = side, .y = (double)-screen_height / ((double)rcd->map_pos.x -
//				(double)p->pos.x + (1.0 - (double)rcd->sign_step.x) / 2.0) / rcd->ray_dir.x});
//	return ((t_point){.x = side, .y = (double)-screen_height / ((double)rcd->map_pos.y -
//			(double)p->pos.y + (1.0 - (double)rcd->sign_step.y) / 2.0) / rcd->ray_dir.y});
double s = sqrt(rcd->side_dis.x * rcd->side_dis.x + rcd->side_dis.y * rcd->side_dis.y);
double c = cos(rcd->cam);
	c = c < 0.0 ? -c : c;
	s = s * c;
	if (s > 1.0)
		return ((t_point){.x = side, .y = screen_height / s});
	return ((t_point){.x = side, .y = screen_height});
}

#define COLOR_SEIL 0x00559F
#define COLOR_FLOOR 0x777777

inline static void	print_line(t_image *img, const int x,
								const t_point side_height)
{
	int	start;
	int	end;

//	printf("line: %i\n", side_height.y);

	if ((start = -side_height.y / 2 + img->size.y / 2) < 0)
		start = 0;
	if ((end = side_height.y / 2 + img->size.y / 2) >= img->size.y)
		end = img->size.y - 1;
	if (start != 0)
		ftx_vertical_line(img, (t_point){x, 0}, (t_point){x, start - 1}, (t_point){COLOR_SEIL, COLOR_SEIL});
//		verLine(x, 0, start - 1, COLOR_SEIL);
	if (side_height.x == 0)
		ftx_vertical_line(img, (t_point){x, start}, (t_point){x, end}, (t_point){0xFFFFFF, 0xFFFFFF});
	else
		ftx_vertical_line(img, (t_point){x, start}, (t_point){x, end}, (t_point){0, 0});
//	verLine(x, start, end, color);
	if (end != img->size.y - 1)
		ftx_vertical_line(img, (t_point){x, end + 1}, (t_point){x, img->size.y}, (t_point){COLOR_FLOOR, COLOR_FLOOR});
//		verLine(x, end + 1, img->size.y, COLOR_FLOOR);
}

void	print(t_image *img)
{
	int 				x;
	t_raycasting_data	data;

	x = -1;
	while (++x < img->size.x)
	{
		prepare(&data, player(), x, img->size.x);
		print_line(img, x, dda_side_height(&data, player(), map(), img->size.y));
	}
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
		player()->pos.x += sin(player()->dir) * player()->speed;
		player()->pos.y += cos(player()->dir) * player()->speed;
	}
	if (key == KEY_D && status == FTX_KEY_STATUS_PRESSED && (up = 1))
	{
		player()->pos.x += sin(player()->dir + M_PI_2) * player()->speed;
		player()->pos.y += cos(player()->dir + M_PI_2) * player()->speed;
	}
	if (key == KEY_S && status == FTX_KEY_STATUS_PRESSED && (up = 1))
	{
		player()->pos.x += sin(player()->dir + M_PI) * player()->speed;
		player()->pos.y += cos(player()->dir + M_PI) * player()->speed;
	}
	if (key == KEY_A && status == FTX_KEY_STATUS_PRESSED && (up = 1))
	{
		player()->pos.x += sin(player()->dir + M_PI + M_PI_2) * player()->speed;
		player()->pos.y += cos(player()->dir + M_PI + M_PI_2) * player()->speed;
	}
	return (sf_call_move((t_window*)data, up));
}

int		call_turn(int key, int status, void *data)
{
	int		up;

	up = 0;
	if (key == KEY_RIGHT && status == FTX_KEY_STATUS_PRESSED && (up = 1))
		player()->dir += player()->fov / 8;
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

	if ((win = ftx_new_window(ft_point(500, 500), "wolf",
								(const uint64_t *)"wolf")) == NULL)
		return ;
	ftx_key_hook(KEY_EXIT, &call_exit, win);
	ftx_key_hook(KEY_W, &call_move, win);
	ftx_key_hook(KEY_A, &call_move, win);
	ftx_key_hook(KEY_S, &call_move, win);
	ftx_key_hook(KEY_D, &call_move, win);
	ftx_key_hook(KEY_RIGHT, &call_turn, win);
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
