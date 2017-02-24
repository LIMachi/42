/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 11:11:43 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/07 19:39:15 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTX_H
# define LIBFTX_H

# include <ftx_macro.h>

typedef struct s_image		t_image;
typedef struct s_mice		t_mice;
typedef struct s_window		t_window;
typedef struct s_key_data	t_key_data;
typedef struct s_ftx_data	t_ftx_data;
typedef struct s_cimg		t_cimg;

struct						s_cimg
{
	int		width;
	int		height;
	char	*buffer;
	float	vertex[8];
	t_cimg	*next;
};

/*
** t_image:
** img:						pointer to an opaque object image from mlx
** data:					pointer to raw bmp data of image
** bpp (bites per pixel):	number of bites used to represent a color
** size_line:				number of bytes to store a single line of pixels
** endian:					endian (byte order) of raw bmp data
** size:					size (in pixels) of the image
** cursor:					position at wich ftx_write will put characters
** tick:					number of rougthly 60th of second since start
*/

struct						s_image
{
	t_cimg			*img;
	int				*data;
	int				bpp;
	int				size_line;
	int				endian;
	t_point			size;
	t_point			cursor;
	unsigned int	tick;
};

/*
** t_key_data:
** status:		status of the key (RELEASED, PRESSED, DOUBLED, HOLD)
** callback:	function to callback on changement in status
** data:		pointer to data to be sent to callback
** tick:		tick of the last update
*/

struct						s_key_data
{
	int				status;
	int				(*callback)(int key, int status, void *data);
	void			*data;
	unsigned int	tick;
};

/*
** t_mice:
** pos:			position of the cursor
** click_pos:	position of the last click (for dragging)
** callback:	pointer to function to be called when the mice move
** data:		data to be sent to the callback
** keymap:		mice keymap (see t_key_data)
*/

struct						s_mice
{
	t_point			pos;
	t_point			click_pos;
	int				(*callback)(t_point pos, t_point click_pos, void *data);
	void			*data;
	t_key_data		keymap[10];
};

/*
** t_window:
** win:		pointer to an opaque object window from mlx
** name:	string containing the name of the window
** size:	size (in pixels) of the (inner part of the) window
** vbuffer:	video buffer, image to be print on the window on update
** mice:	mice data (more information: t_mice)
*/

struct						s_window
{
	void			*win;
	char			*name;
	t_point			size;
	t_image			*vbuffer;
	t_mice			mice;
};

/*
** t_ftx_data:
** mlx:				pointer to an opaque object mlx from mlx
** windows:			list of windows currently oppened by mlx
** images:			list of currently oppened images by mlx
** focused_window:	pointer to the focused window
** tick:			current tick of execution (around 60th of seconds)
** keymap:			keyboard keymap (see t_key_data)
*/

struct						s_ftx_data
{
	void				*mlx;
	t_2list				*windows;
	t_2list				*images;
	t_window			*focused_window;
	unsigned int		tick;
	int					(*loop_callback)(t_ftx_data *data);
	t_key_data			keymap[KEYMAP_SIZE];
};

/*
** t_ftx_line_data: (structure to store bresenham algorithm's variables)
** v
** a	coordinates of first point
** b	coordinates of second point
** d	delta (x per y or y per x)
** s	sign (of movement)
** cr	set of 2 value to calculate the red component
** cg	set of 2 value to calculate the green component
** cb	set of 2 value to calculate the blue component
*/

typedef struct				s_ftx_line_data
{
	int					v;
	t_point				a;
	t_point				b;
	t_point				d;
	t_point				s;
	double				cr[2];
	double				cg[2];
	double				cb[2];
}							t_ftx_line_data;

/*
** ftx_data: return a pointer to a global data of type t_ftx_data
** when called for the first time, it will initialize it's mlx pointer
*/

t_ftx_data					*ftx_data(void);

/*
** ftx_color_lerp: do a linear interpolation betwen f (front) and b (back)
*/

int							ftx_color_lerp(const int f, const int b, double v);

int							ftx_hook_mice_button(t_window *window, int button,
				int (*callback)(int key, int status, void *data), void *data);
int							ftx_hook_mice_move(
								t_window *window, int (*callback)(t_point pos,
								t_point click_pos, void *data), void *data);

/*
** ftx_put_pixel_img: put in img at the coord x, y a pixel
** might segfault if pos is not in img
** return the pointer to img passed in arg
*/

t_image						*ftx_put_pixel_img(t_image *img, const int x,
												const int y, const int color);

/*
** ftx_pixel same as ftx_put_pixel_img with a clipping (no segfault on invalid
** position)
*/

t_image						*ftx_pixel(t_image *img, const int x, const int y,
										const int color);

/*
** ftx_img_to_img: put img at coord pos on out with a bit mask on each color
** return the pointer to img passed in arg
*/

t_image						*ftx_img_to_img(t_image *out, const t_point pos,
											const t_image *img, int mask);

/*
** ftx_line: print in img a line starting at a and go** tick
** number of rougthly 60th of second since starting to b, with a color
** transition from color.x to color.y
** current version of ftx_line does not have clipping
** return the pointer to img passed in arg
*/

t_image						*ftx_line(t_image *img, t_point a, t_point b,
										t_point color);

/*
** ftx_vertical_line: print in img a vertical line starting at a.x, a.y and
** going to a.x, b.y, with a color transition from color.x to color.y
** return the pointer to img passed in arg
*/

t_image						*ftx_vertical_line(t_image *img, t_point a,
												t_point b, t_point color);

/*
** ftx_horizontal_line: print in img a horizontal line starting at a.x, a.y and
** going to b.x, a.y, with a color transition from color.x to color.y
** return the pointer to img passed in arg
*/

t_image						*ftx_horizontal_line(t_image *img, t_point a,
												t_point b, t_point color);

/*
** ftx_write: similar to write, but put characters as font in img
** return the number of characters printed
*/

size_t						ftx_write(t_image *img, char *str, size_t count,
									int color);

/*
** will print the image vbuffer of window onto window
** this function is called on forced reprint (expose/focus)
*/

int							ftx_window_refresh(void);

/*
** ftx_start: will start the X server. This function should not return.
** To exit the X server, call ftx_end()
*/

void						ftx_start(void);

/*
** ftx_end: will clear all internal ftx data, then call exit ()
*/

void						ftx_end(void);

/*
** ftx_free_window: free the window and his content
*/

int							ftx_free_window(const uint64_t *id);

/*
** ftx_new_window: prepare a new window and his vbuffer
*/

t_window					*ftx_new_window(const t_point size,
										const char *name, const uint64_t *id);

/*
** ftx_free_image: free image passed in arg
*/

int							ftx_free_image(t_image *img);

/*
** ftx_new_image: create a new image of size passed in arg
*/

t_image						*ftx_new_image(t_point size);

/*
** ftx_refresh_window: print the vbuffer image of window
*/

int							ftx_refresh_window(t_window *win);

/*
** ftx_key_hook: hook a key update (press, release, repeat, etc...) with a
** callback. on any key update, the callback will be executed with a single
** parameter (void *data)
*/

int							ftx_key_hook(int key, int (*callback)(int key,
										int status, void *data), void *data);

/*
** ftx_key_status return a pointer to the status older of keycode
*/

int							*ftx_key_status(int keycode);

/*
** ftx_put_selection_square will put a partially transparent square on img
** between point a and b with filled with color (borders are more visible than
** iner)
*/

t_image						*ftx_put_selection_square(t_image *img,
							const t_point a, const t_point b, const int color);

/*
** return the color value of a pixel of img at the coord x,y
*/

int							ftx_get_pixel_img(t_image *img, const int x,
											const int y);

/*
** put a pixel on img with the color blended between the current visible pixel
** and the one pending to be print (value determine the blending)
*/

t_image						*ftx_slerp_pixel(t_image *img, const t_point pos,
										const int color, const double value);

/*
** ftx_fill_image fill img with color multplied by value (0 to 1 double)
*/

t_image						*ftx_fill_image(t_image *img, const int color,
										const double value);

/*
** does not work for now, make invalid bmp files
*/

int							ftx_screenshoot(t_window *win,
											const char *folder_path);

int							*ftx_button_status(int button);
t_image						*ftx_set_cursor(t_image *img, int x, int y);
t_image						*ftx_put_ubmp_img(t_image *out, const t_point pos,
												const t_ubmp *img, int mask);

int							ftx_loop_hook(
										int (*loop_callback)(t_ftx_data *data));
#endif
