/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 11:11:43 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/17 14:08:53 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTX_H
# define LIBFTX_H
# include <libft.h>
# include <ftx_macro.h>
# include <mlx.h>

# define FTX_KEY_STATUS_PRESSED 1
# define FTX_KEY_STATUS_HOLD 2
# define FTX_KEY_STATUS_RELEASED 0
# define FTX_KEY_STATUS_DOUBLED 3

/*
** t_image:
** img						pointer to an opaque object image from mlx
** data						pointer to raw bmp data of image
** bpp (bites per pixel)	number of bites used to represent a color
** size_line				number of bytes to store a single line of pixels
** endian					endian (byte order) of raw bmp data
** size						size (in pixels) of the image
** cursor					position at wich ftx_write will put characters
** tick						number of rougthly 60th of second since start
*/

typedef struct	s_image
{
	void			*img;
	int				*data;
	int				bpp;
	int				size_line;
	int				endian;
	t_point			size;
	t_point			cursor;
	unsigned int	tick;
}				t_image;

/*
** t_mice:
** pos						position of the cursor
** click_pos				position of the last click (for dragging)
** click_tick				tick of the start of the actual click
** int	last_click_release	tick of the end of last click
** int	click_button		last Buttonpress update (mask)
*/

typedef struct	s_mice
{
	t_point			pos;
	t_point			click_pos;
	unsigned int	click_tick;
	unsigned int	last_click_release;
	unsigned int	click_button;
}				t_mice;

/*
** t_window:
** win		pointer to an opaque object window from mlx
** mice		mice data (more information: t_mice)
*/

typedef struct	s_window
{
	void			*win;
	t_point			size;
	t_image			*vbuffer;
	t_mice			mice;
}				t_window;
/*
** t_ftx_data:
** mlx		pointer to an opaque object mlx from mlx
*/

typedef int (*t_keymap_callback)(int key, int status, void *data);

typedef struct	s_key_data
{
	int					status;
	t_keymap_callback	callback;
	void				*data;
	unsigned int		tick;
}				t_key_data;

typedef struct	s_ftx_data
{
	void				*mlx;
	t_2list				*windows;
	t_2list				*images;
	t_window			*focused_window;
	unsigned int		tick;
	t_key_data			keymap[KEYMAP_SIZE];
}				t_ftx_data;

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

typedef struct			s_ftx_line_data
{
	int					v;
	t_point				a;
	t_point				b;
	t_point				d;
	t_point				s;
	double				cr[2];
	double				cg[2];
	double				cb[2];
}						t_ftx_line_data;

/*
** ftx_data: return a pointer to a global data of type t_ftx_data
** when called for the first time, it will initialize it's mlx pointer
*/

t_ftx_data	*ftx_data(void);

/*
** ftx_color_lerp: do a linear interpolation betwen f (front) and b (back)
*/

int			ftx_color_lerp(const int f, const int b, double v);

/*
** hook the function mice_update_func to the mice updates in window
** return 0 on succes, -1 on failure
*/

int			ftx_hook_mice(t_window *window, int (*mice_update_func)(void *data),
 							void *data);

/*
** ftx_put_pixel_img: put in img at the coord x, y a pixel
** might segfault if pos is not in img
** return the pointer to img passed in arg
*/

t_image		*ftx_put_pixel_img(t_image *img, const int x, const int y,
								const int color);

/*
** ftx_pixel same as ftx_put_pixel_img with a clipping (no segfault on invalid
** position)
*/

t_image		*ftx_pixel(t_image *img, const int x, const int y, const int color);

/*
** ftx_img_to_img: put img at coord pos on out with a bit mask on each color
** return the pointer to img passed in arg
*/

t_image		*ftx_img_to_img(t_image *out, const t_point pos, const t_image *img,
							int mask);

/*
** ftx_line: print in img a line starting at a and go** tick		number of rougthly 60th of second since start
ing to b, with a color
** transition from color.x to color.y
** current version of ftx_line does not have clipping
** return the pointer to img passed in arg
*/

t_image		*ftx_line(t_image *img, t_point a, t_point b, t_point color);

/*
** ftx_vertical_line: print in img a vertical line starting at a.x, a.y and
** going to a.x, b.y, with a color transition from color.x to color.y
** return the pointer to img passed in arg
*/

t_image		*ftx_vertical_line(t_image *img, t_point a, t_point b,
								t_point color);

/*
** ftx_horizontal_line: print in img a horizontal line starting at a.x, a.y and
** going to b.x, a.y, with a color transition from color.x to color.y
** return the pointer to img passed in arg
*/

t_image		*ftx_horizontal_line(t_image *img, t_point a, t_point b,
								t_point color);

/*
** ftx_write: similar to write, but put characters as font in img
** return the number of characters printed
*/

size_t		ftx_write(t_image *img, char *str, size_t count, int color);

/*
** will print the image vbuffer of window onto window
** this function is called on forced reprint (expose/focus)
*/

int			ftx_window_refresh(void);

/*
** ftx_start: will start the X server. This function should not return.
** To exit the X server, call ftx_end()
*/

void		ftx_start(void);

/*
** ftx_end: will clear all internal ftx data, then call exit ()
*/

void		ftx_end(void);

/*
** ftx_free_window: free the window and his content
*/

int			ftx_free_window(const uint64_t *id);

/*
** ftx_new_window: prepare a new window and his vbuffer
*/

t_window	*ftx_new_window(const t_point size, const char *name,
							const uint64_t *id);

int			ftx_free_image(t_image *img);
t_image		*ftx_new_image(t_point size);
int			ftx_refresh_window(t_window *win);
int			ftx_key_hook(int key, t_keymap_callback callback, void *data);
int			*ftx_key_status(int keycode);

#endif
