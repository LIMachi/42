/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/15 00:17:18 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/08 06:19:41 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTX_H
# define FTX_H

# if !defined(NORM42)
#  define NORM42 0
# endif

# include <libft.h>
# include <mlx.h>
# if NORM42 == 0
#  include <time.h>
# endif
# if DEBUG == 1
#  include <stdio.h> //
# endif
//# include <stdint.h>
# include <math.h>

# define SIN(x) sin(x)
# define COS(x) cos(x)

# define GDX_NEW 1
# define GDX_FREE 2
# define GDX_ACCES 4

# define NOMASK 0xFFFFFFFF
# define UNASCII 0
# define CRSIZE 12

# define WHITE 0xFFFFFF
# define GRAY 0x777777
# define BLACK 0x000000
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define CIAN 0x00FFFF
# define YELLOW 0xFFFF00
# define MAGENTA 0xFF00FF

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
#  define KEY_PAD_PLUS 69
#  define KEY_PAD_MINUS 78
#  define KEY_CTRL_LEFT 256
#  define KEY_PAD_0 82
#  define KEY_X 7
#  define KEY_Y 16
#  define KEY_Z 6
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

typedef struct			s_object3d_base
{
	t_vector			rotation_axis_x;
	t_vector			rotation_axis_y;
	t_vector			rotation_axis_z;
	t_quaternion		orientation_quaternion;
	t_vector			position;
}						t_object3d_base;

typedef struct			s_camera
{
	t_object3d_base		object;
	t_vector			focal;
	t_vector			focus;
}						t_camera;

typedef struct			s_line_ref
{
	int					start;
	int					end;
}						t_line_ref;

typedef struct			s_object3d
{
	t_object3d_base		object;
	int					nb_points;
	t_vector			*points3d_original;
	int					*colors;
	t_vector			*points3d;
	t_point				*points2d;
	int					nb_lines;
	t_line_ref			*lines;
}						t_object3d;

typedef struct			s_scene
{
	int					nb_cameras;
	int					focused_camera;
	t_camera			*cameras;
	int					nb_object3d;
	t_object3d			*objects3d;
	t_point				render_size;
	uint32_t			*colors;
	double				*depth;
	int					*controller;
}						t_scene;

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

t_window				*ftx_get_window(int id);
int						ftx_free_all_windows(t_window *win);
int						ftx_free_window(t_window *win);
t_window				*ftx_new_window(t_point size, char *name, int wfps);
int						ftx_add_window(t_window *win);

t_image					*ftx_get_image(t_window *win, int id);
t_image					*ftx_new_image(t_point size);
int						ftx_free_image(t_image *img);
int						ftx_free_all_images(t_image *img);
void					ftx_add_image(t_window *win, t_image *img, int id);

t_vector				ft_pt3sub(t_vector a, t_vector b);
t_vector				ft_pt3add(t_vector a, t_vector b);

t_point					ft_ptsub(t_point a, t_point b);
t_point					ft_ptadd(t_point a, t_point b);
void					ft_ptswap(t_point *a, t_point *b);

void					ftx_print_char(t_image *img, t_point pos, int color,
										char c);
void					ftx_print_str(t_image *img, t_point pos, int color,
										char *str);

void					ftx_clear_img(t_image *img);
void					ftx_put_img_to_img(t_image *out, t_image *img,
											unsigned int mask);
void					ftx_putpixelimg(t_image *img, t_point pos, int color);

int						ftx_motion_hook(int x, int y, void *p);
int						ftx_keypress_hook(int key, void *p);
int						ftx_keyrelease_hook(int key, void *p);
int						ftx_buttonpress_hook(int key, int x, int y, void *p);
int						ftx_buttonrelease_hook(int key, int x, int y, void *p);

void					init_mlx_data(void);

t_point					ft_get_width(char c);

int						ft_bonus_read(const char *filepath, char **out);

int						ftx_fixtorgb(t_fix r, t_fix g, t_fix b);
void					sf_draw_scene(t_mlx_data *data, t_image *img);
int						sf_clip(t_point *a, t_point *b, t_point c, t_point d);
int						sf_color_mix(int s, int e, t_fix f);
void					ftx_putpixelimg(t_image *img, t_point pos, int color);
int						ft_ptequal(t_point a, t_point b);
t_point					*sf_iintersection(t_point a, t_point b, t_point c, t_point d);
void					ftx_pixel(t_image *img, int x, int y, int color);
void					ftx_horizontal_line(t_image *img, t_point a, t_point b, t_point color);
void					ftx_vertical_line(t_image *img, t_point a, t_point b, t_point color);
void					ftx_line(t_image *img, t_point a, t_point b, t_point color);
t_mlx_data				*ftx_data(int flag);
unsigned long long int	ft_bswap64(unsigned long long int x);
unsigned long int		ft_bswap32(unsigned long int x);
unsigned short int		ft_bswap16(unsigned short int x);

char					**read_xpm3(const char *path);

#endif
