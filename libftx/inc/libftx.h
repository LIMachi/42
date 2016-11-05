/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/15 00:17:18 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/05 19:30:20 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTX_H
# define LIBFTX_H

# include <mlx.h>

# if !defined(NORM_42) || NORM_42 == 0
#  include <time.h>
# endif

# if defined(DEBUG) || DEBUG == 1
#  include <stdio.h>
# endif

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
	t_point				joystick;
}						t_mice;

typedef struct			s_line_ref
{
	int					start;
	int					end;
}						t_line_ref;

typedef struct			s_mlx_data
{
	void				*mlx;
	t_window			*windows;
	int					focused_window;
	int					keymap[KEYMAPSIZE];
	t_mice				mice;
	int					update;
}						t_mlx_data;

/*
** a button is an interactive immage (can be clicked, toggle, holded, slided,
** etc)
*/

/*
** s_button (type = 0, unknown button type) is a cast to get common values from
** any type of button and easily race a multi-type linked list of buttons (note
** that the more buttons there is in a window, the longer will the update be)
*/

typedef struct			s_button
{
	const uint8_t		type;
	t_point				position;
	t_point				hitbox;
	struct s_button		*prev_button;
	struct s_button		*next_button;
}						t_button;

/*
** t_button_click (type = 1) send an update to trigger when released
*/

typedef struct			s_button_click
{
	const uint8_t		type;
	t_point				position;
	t_point				hitbox;
	t_button			*prev_button;
	t_button			*next_button;
	t_ubmp				*released;
	t_ubmp				*hover;
	t_ubmp				*click;
	t_int_func_undef	trigger;
}						t_button_click;

/*
** t_button_maintain (type = 2) send an update to trigger has long has it is
** maintained
*/

typedef struct			s_button_maintain
{
	const uint8_t		type;
	t_point				position;
	t_point				hitbox;
	t_button			*prev_button;
	t_button			*next_button;
	t_ubmp				*released;
	t_ubmp				*hover;
	t_ubmp				*maintained;
	t_int_func_undef	trigger;
}						t_button_maintain;

/*
** t_button_toggle (type = 3) change state when released and send an update to
** the corresponding function for his new state
*/

typedef struct			s_button_toggle
{
	const uint8_t		type;
	t_point				position;
	t_point				hitbox;
	t_button			*prev_button;
	t_button			*next_button;
	t_ubmp				*off;
	t_ubmp				*hover_off;
	t_ubmp				*hover_on;
	t_ubmp				*on;
	uint8_t				state;
	t_int_func_undef	toggled_on;
	t_int_func_undef	toggled_off;
}						t_button_toggle;

/*
** t_button_slider (type = 4) whil triger slider_moved if a click or maintained
** slide is made in his hitbox and will send the position of the slider to
** slider_moved
*/

typedef struct			s_button_slider
{
	const uint8_t		type;
	t_point				position;
	t_point				hitbox;
	t_button			*prev_button;
	t_button			*next_button;
	t_ubmp				*back;
	t_ubmp				*slider;
	uint8_t				constraints;
	t_point				slider_position;
	t_int_func_undef	slider_moved;
}						t_button_slider;

/*
** t_button_text_box (type = 5) is particular, it will catch keyboard updates
** and write the input to a box, waiting to get an "enter key" signal to send
** the stored text to his function. a click update will change the position
** of the cursor, and so the way the text is input
*/

typedef struct			s_button_text_box
{
	const uint8_t		type;
	t_point				position;
	t_point				hitbox;
	t_button			*prev_button;
	t_button			*next_button;
	t_ubmp				*back;
	t_ubmp				*back_hover;
	char				*str;
	char				cursor_symbol;
	uint32_t			color;
	t_point				cursor_position;
	uint32_t			max_text;
	t_int_func_undef	get_text;
}						t_button_text_box;

/*
** t_font				*font;
*/

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

void					ftx_init_mlx_data(void);

t_point					ftx_get_width(char c);

int						sf_clip(t_point *a, t_point *b, t_point c, t_point d);
int						sf_color_mix(int s, int e, t_fix f);
void					ftx_putpixelimg(t_image *img, t_point pos, int color);

void					ftx_pixel(t_image *img, int x, int y, int color);
void					ftx_horizontal_line(t_image *img, t_point a, t_point b,
																t_point color);
void					ftx_vertical_line(t_image *img, t_point a, t_point b,
																t_point color);
void					ftx_line(t_image *img, t_point a, t_point b,
																t_point color);
t_mlx_data				*ftx_data(int flag);

int						ftx_color_multiply(int color, double mult);

int						ftx_update(void *ptr);
void					ftx_error(char *str);
void					sf_update(int up, t_fdf *fdf, t_image *img,
													t_window *win);

#endif
