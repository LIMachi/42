/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/15 00:17:18 by hmartzol          #+#    #+#             */
/*   Updated: 2016/07/12 19:16:28 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTX_H
# define FTX_H

# include <libft.h>
# include <mlx.h>
# include <time.h>

# define GDX_NEW 1
# define GDX_FREE 2
# define GDX_ACCES 4

# define ZMX 10
# define ZMY 10
# define SPX 25
# define SPY 25
# define SPEED 1

# define COLORSWAP(c) ((c & 0xFF00) | (c & 0xFF) << 16 | (c & 0xFF0000) >> 16)

# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF

# if OS == LINUX
#  define KEYMAPSIZE 65535
#  define KEY_EXIT 65307
#  define KEY_UP 65362
#  define KEY_LEFT 65361
#  define KEY_DOWN 65364
#  define KEY_RIGHT 65363
#  define KEY_PAD_PLUS 65451
#  define KEY_PAD_MINUS 65453
#  define KEY_ENTER 65293
#  define KEY_PAD_0 65438
#  define KEY_CTRL_RIGHT 65508
#  define KEY_CTRL_LEFT 65507
#  define KEY_SPACE 32
#  define KEY_0 48
#  define KEY_1 49
#  define KEY_2 50
#  define KEY_3 51
#  define KEY_4 52
#  define KEY_5 53
#  define KEY_6 54
#  define KEY_7 55
#  define KEY_8 56
#  define KEY_9 57
#  define KEY_A 97
#  define KEY_B 98
#  define KEY_C 99
#  define KEY_D 100
#  define KEY_E 101
#  define KEY_F 102
#  define KEY_G 103
#  define KEY_H 104
#  define KEY_I 105
#  define KEY_J 106
#  define KEY_K 107
#  define KEY_L 108
#  define KEY_M 109
#  define KEY_N 110
#  define KEY_O 111
#  define KEY_P 112
#  define KEY_Q 113
#  define KEY_R 114
#  define KEY_S 115
#  define KEY_T 116
#  define KEY_U 117
#  define KEY_V 118
#  define KEY_W 119
#  define KEY_X 120
#  define KEY_Y 121
#  define KEY_Z 122
#  define KEY_SHIFT_LEFT 65505
#  define KEY_SHIFT_RIGHT 65506
#  define MICE_SCROLL_UP 4
#  define MICE_SCROLL_DOWN 5
# elif OS == MACINTOCH
#  define KEYMAPSIZE 280
#  define KEY_EXIT 53
#  define KEY_UP 126
#  define KEY_LEFT 123
#  define KEY_DOWN 125
#  define KEY_RIGHT 124
# endif

# define C_FDF 1
# define C_TERM 2
# define C_BUTTON 4

typedef struct			s_image
{
	t_point				size;
	void				*ptr;
	int					bpp;
	int					size_line;
	int					endian;
	int					*data;
	t_point				pos;
	struct s_image		*next;
	struct s_image		*prev;
	int					id;
	int					update;
	t_int_func_undef	fill_func;
}						t_image;

typedef struct			s_window
{
	void				*win;
	t_point				size;
	t_image				*vbuffer;
	t_image				*images;
	int					fps;
	int					wfps;
	struct s_window		*next;
	struct s_window		*prev;
	int					id;
	t_int_func_undef	up_func;
	int					frames;
	int					frameloss;
	int					last_frame;
	struct timespec		last_time;
	int					use_code;
	void				*data;
	double				zoom;
}						t_window;

typedef struct			s_mice
{
	int					map[10];
	int					flags;
	t_point				pos;
	t_point				drag;
}						t_mice;

typedef struct			s_mat_r
{
	t_point3d			r;
	double				m[3][3];
}						t_mat_r;

typedef struct			s_fdf
{
	int					***map;
	t_point				size;
	t_point3d			**map3;
	t_point				**map2;
	t_mat_r				*rotation;
	t_point3d			eye;
	t_point3d			camera_pos;
	t_point3d			camera_line;
}						t_fdf;

typedef struct			s_mlx_data
{
	void				*mlx;
	t_window			*windows;
	int					focused_window;
	int					keymap[KEYMAPSIZE];
	t_mice				mice;
	int					update;
}						t_mlx_data;

typedef struct			s_vtff_la_norme_0
{
	int					v;
	t_point				a;
	t_point				b;
	t_point				d;
	t_point				s;
	t_fix				cr[2];
	t_fix				cg[2];
	t_fix				cb[2];
}						t_vtff_la_norme_0;

int						ftx_fixtorgb(t_fix r, t_fix g, t_fix b);
void					sf_draw_scene(t_mlx_data *data, t_image *img);
int						sf_clip(t_point *a, t_point *b, t_point c, t_point d);
void					sf_ptswap(t_point *a, t_point *b);
int						sf_color_mix(int s, int e, t_fix f);
void					ftx_putpixelimg(t_image *img, t_point pos, int color);
int						ft_ptequal(t_point a, t_point b);
t_point					*sf_iintersection(t_point a, t_point b, t_point c, t_point d);
void					ftx_pixel(t_image *img, int x, int y, int color);
void					ftx_horizontal_line(t_image *img, t_point a, t_point b, t_point color);
void					ftx_vertical_line(t_image *img, t_point a, t_point b, t_point color);
void					ftx_line(t_image *img, t_point a, t_point b, t_point color);
t_mlx_data				*ftx_data(int flag);

#endif
