/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_4.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/27 10:28:10 by hmartzol          #+#    #+#             */
/*   Updated: 2017/03/02 12:52:03 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECT_4_H
# define CONNECT_4_H

# include <stdlib.h>
# include <fcntl.h>
# include <libft.h>
# include <time.h>
# include <mlx.h>

/*
** # include <X11/X.h>
*/

# define MINIMUM_WIN_WIDTH 400
# define MINIMUM_WIN_HEIGHT 400
# define MINIMUM_GRID_WIDTH 7
# define MINIMUM_GRID_HEIGHT 6
# define STONES_TO_CONNECT 4
# define MAX_TICK 100000

# define KEYPRESS 2
# define KEYPRESSMASK (1L<<0)
# define KEYRELEASE 3
# define KEYRELEASEMASK (1L<<1)
# define BUTTONPRESS 4
# define BUTTONPRESSMASK (1L<<2)
# define BUTTONRELEASE 5
# define BUTTONRELEASEMASK (1L<<3)
# define MOTIONNOTIFY 6
# define POINTERMOTIONMASK (1L<<6)

# define MODE_FILL 2
# define MODE_ANDRES 1

typedef struct	s_pixel
{
	t_point		pos;
	int			color;
}				t_pixel;

typedef struct	s_mlx
{
	int			mode;
	void		*ptr;
	void		*win;
	void		*img;
	char		*data;
	int			bpp;
	int			sl;
	int			endian;
	int			keymap[270];
	int			micemap[7];
	t_point		win_size;
	int			**grid;
	t_point		grid_size;
	int			*stop;
}				t_mlx;

int		**c4_prepare_grid(int argc, char **argv, t_point *size);
int		c4_put_stone(int **grid, int column, int player, t_point size);
void	c4_print_grid(t_mlx mlx);
int		c4_check_grid(int **grid, t_point size);
int		c4_ia_input(int **grid, int player, t_point size);
void	c4_clear_screen(void);
int		c4_player_input(t_mlx mlx);
void	c4_wait(int seconds);

int		check_v(int **grid, int player, t_point size, t_point t);
int		verif_v(int **grid, int player, t_point size, t_point t);
int		verif_h(int **grid, int player, t_point size, t_point t);
int		check_h(int **grid, int player, t_point size, t_point t);
int		check(int **grid, int player, t_point size, t_point t);
int		verif_d_2(int **grid, int player, t_point size, t_point t);

void	ftx_hook_keyinit(t_mlx *obj);
void	ftx_hook_miceinit(t_mlx *obj);
void	ftx_put_pixel_img(t_mlx mlx, int x, int y, int color);
void	ftx_put_circle(t_mlx mlx, t_pixel center, int radius, int mode);
void	ftx_put_square(t_mlx mlx, t_pixel corner, t_point size);
void	ftx_expose(void *param);
void	ftx_clear_img(t_mlx mlx);
void	ftx_quit(t_mlx mlx);

#endif
