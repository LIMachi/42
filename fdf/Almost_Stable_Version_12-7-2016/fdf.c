/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/15 00:21:53 by hmartzol          #+#    #+#             */
/*   Updated: 2016/07/12 19:24:47 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftx.h>
#include <stdio.h>
#include <math.h>

/*
static const int64_t g[96] = {
	0b0010000100001000010000100001000010000000001000000000000, // ! 33
	0b0101001010010100000000000000000000000000000000000000000, // " 34
	0b0000000000010100101011111010101111101010010100000000000, // # 35
	0b0010001111101001010001110001010010111110001000000000000, // $ 36
	0b0100110101010100001000100010000101010101100100000000000, // % 37
	0b0000001000101001010001000101001001110010011010000000000, // & 38
	0b0010000100001000000000000000000000000000000000000000000, // ' 39
	0b0010001000010001000010000100001000010000010000100000100, // ( 40
	0b0010000010000100000100001000010000100001000100001000100, // ) 41
	0b0000000100101010111010101001000000000000000000000000000, // * 42
	0b0000000000000000010000100111110010000100000000000000000, // + 43
	0b0000000000000000000000000000000000000110001000100000000, // , 44
	0b0000000000000000000000000111110000000000000000000000000, // - 45
	0b0000000000000000000000000000000000000100011100010000000, // . 46
	0b0000000001000010001000010001000100001000100001000000000, // / 47
	0b0010001010100011000110001100011000101010001000000000000, // 0 48
	0b0010001100101000010000100001000010000100111110000000000, // 1 49
	0b0111010001100010000100010001000100010000111110000000000, // 2 50
	0b1111100001000100010001110000010000110001011100000000000, // 3 51
	0b0001000010001100101001010100101111000010000100000000000, // 4 52
	0b1111110000100001011011001000010000110001011100000000000, // 5 53
	0b0111010001100001000011110100011000110001011100000000000, // 6 54
	0b1111100001000100001000100001000100001000010000000000000, // 7 55
	0b0111010001100011000101110100011000110001011100000000000, // 8 56
	0b0111010001100011000101111000010000110001011100000000000, // 9 57
	0b0000000000001000111000100000000000000100011100010000000, // : 58
	0b0000000000001000111000100000000000000110001000100000000, // ; 59
	0b0000000001000100010001000100000100000100000100000100000, // < 60
	0b0000000000000000000011111000001111100000000000000000000, // = 61
	0b0000010000010000010000010000010001000100010001000000000, // > 62
	0b0000001110100010000100001000100010000100000000010000000, // ? 63
	0b0111010001100011000110011101011011010000011110000000000, // @ 64
	0b0010001010100011000110001111111000110001100010000000000, // A 65
	0b1111001001010010100101110010010100101001111100000000000, // B 66
	0b0111010001100001000010000100001000010001011100000000000, // C 67
	0b1111001001010010100101001010010100101001111100000000000, // D 68
	0b1111110000100001000011110100001000010000111110000000000, // E 69
	0b1111110000100001000011110100001000010000100000000000000, // F 70
	0b0111010001100001000010000100111000110001011100000000000, // G 71
	0b1000110001100011000111111100011000110001100010000000000, // H 72
	0b0111000100001000010000100001000010000100011100000000000, // I 73
	0b0011100010000100001000010000100001010010011000000000000, // J 74
	0b1000110001100101010011000101001001010001100010000000000, // K 75
	0b1000010000100001000010000100001000010000111110000000000, // L 76
	0b1000110001110111010110101100011000110001100010000000000, // M 77
	0b1000111001110011010110101100111001110001100010000000000, // N 78
	0b0111010001100011000110001100011000110001011100000000000, // O 79
	0b1111010001100011000111110100001000010000100000000000000, // P 80
	0b0111010001100011000110001100011000110101011100000100000, // Q 81
	0b1111010001100011000111110101001001010001100010000000000, // R 82
	0b0111010001100001000001110000010000110001011100000000000, // S 83
	0b1111100100001000010000100001000010000100001000000000000, // T 84
	0b1000110001100011000110001100011000110001011100000000000, // U 85
	0b1000110001100011000101010010100101000100001000000000000, // V 86
	0b1000110001100011000110101101011010110101010100000000000, // W 87
	0b1000110001010100101000100010100101010001100010000000000, // X 88
	0b1000110001010100101000100001000010000100001000000000000, // Y 89
	0b1111100001000100001000100010000100010000111110000000000, // Z 90
	0b0111001000010000100001000010000100001000010000100001110, // [ 91
	0b0000010000100000100001000001000001000010000010000100000, // \ 92
	0b0111000010000100001000010000100001000010000100001001110, // ] 93
	0b0000000100010101000100000000000000000000000000000000000, // ^ 94
	0b0000000000000000000000000000000000000000000000000011111, // _ 95
	0b0010000010000000000000000000000000000000000000000000000, // ` 96
	0b0000000000000000111000001011111000110011011010000000000, // a 97
	0b1000010000100001111010001100011000110001111100000000000, // b 98
	0b0000000000000000111010001100001000010001011100000000000, // c 99
	0b0000100001000010111110001100011000110001011110000000000, // d 100
	0b0000000000000000111010001111111000010001011100000000000, // e 101
	0b0011001001010000100011110010000100001000010000000000000, // f 102
	0b0000000000000000111010001100011000101111000011000101110, // g 103
	0b1000010000100001011011001100011000110001100010000000000, // h 104
	0b0000000100000000110000100001000010000100011100000000000, // i 105
	0b0000000010000000011000010000100001000010100101001001100, // j 106
	0b1000010000100001001010100110001010010010100010000000000, // k 107
	0b1100001000010000100001000010000100001000111000000000000, // l 108
	0b0000000000000001101010101101011010110101100010000000000, // m 109
	0b0000000000000001011011001100011000110001100010000000000, // n 110
	0b0000000000000000111010001100011000110001011100000000000, // o 111
	0b0000000000000001111010001100011000111110100001000010000, // p 112
	0b0000000000000000111110001100011000101111000010000100001, // q 113
	0b0000000000000001011011001100001000010000100000000000000, // r 114
	0b0000000000000000111010001011000001010001011100000000000, // s 115
	0b0000001000010001111001000010000100001001001100000000000, // t 116
	0b0000000000000001000110001100011000110011011010000000000, // u 117
	0b0000000000000001000110001100010101001010001000000000000, // v 118
	0b0000000000000001000110001101011010110101010100000000000, // w 119
	0b0000000000000001000101010001000010001010100010000000000, // x 120
	0b0000000000000001000110001100011001101101000011000101110, // y 121
	0b0000000000000001111100010001000100010000111110000000000, // z 122
	0b0001100100001000010000100110000010000100001000010000011, // { 123
	0b0000000100001000010000100001000010000100001000010000000, // | 124
	0b1100000100001000010000100000110010000100001000010011000, // } 125
	0b0000001001101011001000000000000000000000000000000000000  // ~ 126
};
*/

t_point	ft_ptadd(t_point a, t_point b)
{
	return ((t_point){a.x + b.x, a.y + b.y});
}

t_point	ft_ptsub(t_point a, t_point b)
{
	return ((t_point){a.x - b.x, a.y - b.y});
}

t_point3d	ft_pt3add(t_point3d a, t_point3d b)
{
	return ((t_point3d){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_point3d	ft_pt3sub(t_point3d a, t_point3d b)
{
	return ((t_point3d){a.x - b.x, a.y - b.y, a.z - b.z});
}

#define SIN(x) sin(x)
#define COS(x) cos(x)

void		ft_update_rotation_matrix(t_mat_r *mat)
{
	t_point3d	s;
	t_point3d	c;

	s = (t_point3d){SIN(mat->r.x), SIN(mat->r.y), SIN(mat->r.z)};
	c = (t_point3d){COS(mat->r.x), COS(mat->r.y), COS(mat->r.z)};
	*mat = (t_mat_r){mat->r,
		{{c.z * c.y, c.z * s.y * s.x - s.z * c.x, c.z * s.y * c.x - s.z * s.x},
		{s.z * c.y, s.z * s.y * s.x + c.x * c.z, s.z * s.y * c.x - c.z * s.x},
		{-s.y, s.x * c.y, c.x * c.y}}};
}

t_point3d	ft_matmultvect(t_mat_r *mat, t_point3d vect, t_point3d center)
{
	t_point3d	tmp;

	tmp = ft_pt3sub(vect, center);
	return ((t_point3d){
		mat->m[0][0] * tmp.x + mat->m[1][0] * tmp.y + mat->m[2][0] * tmp.z
		+ center.x, mat->m[0][1] * tmp.x + mat->m[1][1] * tmp.y + mat->m[2][1]
		* tmp.z + center.y, mat->m[0][2] * tmp.x + mat->m[1][2] * tmp.y
		+ mat->m[2][2] * tmp.z + center.z});
}

t_point	ft_3d_to_2d(t_point3d eye, t_point screen_center, t_point3d point, double zoom)
{
	return ((t_point){zoom * (eye.z * (point.x - eye.x) / (eye.z + point.z) + eye.x) + screen_center.x,
					zoom * (eye.z * (point.y - eye.y) / (eye.z + point.z) + eye.y) + screen_center.y});
}

void	sf_ptswap(t_point *a, t_point *b)
{
	t_point t;

	t = *a;
	*a = *b;
	*b = t;
}

int		sf_color_mix(int s, int e, t_fix p)
{
	t_fix r;
	t_fix g;
	t_fix b;

	r.FIX_INT = ((s & 0xFF0000) >> 16);
	g.FIX_INT = ((s & 0xFF00) >> 8);
	b.FIX_INT = (s & 0xFF);
	r.i32 += (((e & 0xFF0000) >> 16) - r.FIX_INT) * p.i32;
	g.i32 += (((e & 0xFF00) >> 8) - g.FIX_INT) * p.i32;
	b.i32 += ((e & 0xFF) - b.FIX_INT) * p.i32;
	return (ftx_fixtorgb(r, g, b));
}

t_window	*ftx_get_window(int id)
{
	t_mlx_data	*data;
	t_window	*tmp;

	data = ftx_data(GDX_ACCES);
	if (data->windows == NULL)
		return (NULL);
	tmp = data->windows;
	while (tmp != NULL && tmp->id != id)
		tmp = tmp->next;
	if (tmp && tmp->id == id)
		return (tmp);
	tmp = data->windows->prev;
	while (tmp != NULL && tmp->id != id)
		tmp = tmp->prev;
	if (tmp && tmp->id == id)
		return (tmp);
	return (NULL);
}

t_image	*ftx_get_image(t_window *win, int id)
{
	t_image	*tmp;

	if (win == NULL)
		return (NULL);
	tmp = win->images;
	while (tmp != NULL && tmp->id != id)
		tmp = tmp->next;
	if (tmp && tmp->id == id)
		return (tmp);
	tmp = win->images->prev;
	while (tmp != NULL && tmp->id != id)
		tmp = tmp->prev;
	if (tmp && tmp->id == id)
		return (tmp);
	return (NULL);
}

/*
** legacy version, no local endian check, might segfault
*/

/*
** note: img->endian == 0 little endian (least significant, 1234, {4,3,2,1})
*/

/*
void	ft_putpixelimg(void *mlx, t_image *img, t_point pos, int color)
{
	int		i;

	i = ((img->size_line) * pos.y) + (pos.x * (img->bpp >> 3));
	if (img->endian)
	{
		img->data[i] = mlx_get_color_value(mlx, color >> 16);
		img->data[i + 1] = mlx_get_color_value(mlx, color >> 8);
		img->data[i + 2] = mlx_get_color_value(mlx, color);
	}
	else
	{
		img->data[i] = mlx_get_color_value(mlx, color);
		img->data[i + 1] = mlx_get_color_value(mlx, color >> 8);
		img->data[i + 2] = mlx_get_color_value(mlx, color >> 16);
	}
}
*/

/*
** compressed version, no size_line/bpp/mlx use (potentialy unportable)
*/

/* v1
void	ftx_putpixelimg(t_image *img, t_point pos, int color)
{
	if ((img->endian == 0) ^ (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__))
		img->data[pos.y * img->size.x + pos.x] = color;
	else
		img->data[pos.y * img->size.x + pos.x] = (((color & 0xFF0000) >> 16)
			| (color & 0xFF00) | ((color & 0xFF) << 16)) << 8;
}
*/

// v2
void	ftx_putpixelimg(t_image *img, t_point pos, int color)
{
	if (!((img->endian == 0) ^ (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)))
		__asm__("bswap %0" : "=r" (color) : "0" (color));
	img->data[pos.y * img->size.x + pos.x] = color;
}

/*
** Mask is used to replace a color in img by "transparent", the masked color
** will not be printed on the out image, if mask is equal to NOMASK, then
** no mask will be used and all pixels will be printed.
** The reason the mask used is -1 (0xFFFFFFFF), is because no amount of 32bit
** byte swap can change his value (bswap(-1) == -1), and so you can test
** the mask even if it has been swap before
*/

#define NOMASK 0xFFFFFFFF

void		ftx_put_img_to_img(t_image *out, t_image *img, unsigned int mask)
{
	t_point			pos;
	t_point			limit;
	t_point			d;
	unsigned int	t;

	if (out == NULL || img == NULL)
		return ;
	d = ft_ptsub(img->pos, out->pos);
	if (d.x >= out->size.x || d.x >= out->size.x || d.x + img->size.x < 0 ||
		d.y + img->size.y < 0)
		return ;
	if (mask != NOMASK && !((img->endian == 0) ^ (LOCAL_ENDIAN == BIG_ENDIAN)))
		__asm__("bswap %0" : "=r" (mask) : "0" (mask));
	limit.x = (d.x + img->size.x >= out->size.x) ? out->size.x : img->size.x;
	limit.y = (d.y + img->size.y >= out->size.y) ? out->size.y : img->size.y;
	pos.y = ((d.y > 0) ? - 1 : -d.y - 1);
	while (++pos.y < limit.y && !(0 & (pos.x = ((d.x > 0) ? - 1 : -d.x - 1))))
		while (++pos.x < limit.x)
		{
				t = (unsigned int)img->data[pos.y * img->size.x + pos.x];
				if (out->endian != img->endian)
					__asm__("bswap %0" : "=r" (t) : "0" (t));
				if (mask == NOMASK || t != mask)
					out->data[(pos.y + d.y) * out->size.x + pos.x + d.x] = t;
		}
}

////////////////////////////////////////////////////////////////////////////////

//9  -> tab
//32 -> space
//48 -> 0
//65 -> A
//97 -> a

#define UNASCII 0

static int64_t	code_to_ascii(unsigned char code)
{
	return (code > 126 ? UNASCII : ((int64_t[127]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0x10842108401000, 0x294A0000000000, 0xA57D5F52800, 0x11F4A38A5F1000,
		0x26AA1110AAC800, 0x14A229393400, 0x10840000000000, 0x11088421082104,
		0x10420842108844, 0x957548000000, 0x213E420000, 0x31100, 0x3E000000,
		0x23880, 0x211088844200, 0x11518C63151000, 0x11942108427C00,
		0x3A310888887C00, 0x7C22238218B800, 0x84652A5E10800, 0x7E10B64218B800,
		0x3A3087A318B800, 0x7C221108842000, 0x3A318BA318B800, 0x3A318BC218B800,
		0x47100023880, 0x47100031100, 0x222220820820, 0x7C1F00000,
		0x2082082222200, 0x1D10844420080, 0x3A318CEB683C00, 0x11518C7F18C400,
		0x79294B9294F800, 0x3A30842108B800, 0x79294A5294F800, 0x7E1087A1087C00,
		0x7E1087A1084000, 0x3A30842718B800, 0x46318FE318C400, 0x38842108423800,
		0x1C421084293000, 0x4632A62928C400, 0x42108421087C00, 0x463BAD6318C400,
		0x4739AD6738C400, 0x3A318C6318B800, 0x7A318FA1084000, 0x3A318C631AB820,
		0x7A318FA928C400, 0x3A30838218B800, 0x7C842108421000, 0x46318C6318B800,
		0x46318A94A21000, 0x46318D6B5AA800, 0x462A5114A8C400, 0x462A5108421000,
		0x7C221110887C00, 0x3908421084210E, 0x2104208210420, 0x3842108421084E,
		0x8A8800000000, 0x1F, 0x10400000000000, 0x705F19B400, 0x4210F46318F800,
		0x746108B800, 0x4217C6318BC00, 0x747F08B800, 0x19284790842000,
		0x746317862E, 0x4210B66318C400, 0x806108423800, 0x403084214A4C,
		0x42109531494400, 0x61084210847000, 0xD56B5AC400, 0xB66318C400,
		0x746318B800, 0xF4631F4210, 0x7C63178421, 0xB661084000, 0x745828B800,
		0x108F210849800, 0x8C6319B400, 0x8C62A51000, 0x8C6B5AA800, 0x8A88454400,
		0x8C6336862E, 0xF888887C00, 0xC842130421083, 0x842108421080,
		0x60842106421098, 0x1359000000000})[code]);
}

void	ftx_print_char(t_image *img, t_point pos, int color, char c)
{
	int 		x;
	int 		y;
	t_mlx_data	*data;
	int64_t		t;

	if ((data = ftx_data(GDX_ACCES)) == NULL)
		return ;
	y = -1;
	t = 1;
	while (++y < 11 && (x = -1))
		while (++x < 5)
			if (code_to_ascii(c) & ((t << (4 - x)) << 5 * (10 - y)))
				ftx_putpixelimg(img, ft_ptadd(pos, ft_point(x, y)), color);
}

#define CRSIZE 12

t_point	sf_cursor_move_right(t_point cursor, int movex, int imgx, int startx)
{
	if (cursor.x + movex > imgx)
		return (ft_point(startx, cursor.y + CRSIZE));
	cursor.x += movex;
	return cursor;
}

void	ftx_print_str(t_image *img, t_point pos, int color, char *str)
{
	t_point	cursor;

	if (!(img && str && pos.x > 0 && pos.x < img->size.x && pos.y > 0 &&
		pos.y < img->size.y))
		return ;
	cursor = pos;
	while (*str++ && cursor.y < img->size.y)
		if (str[-1] > 31 && str[-1] < 127)
		{
			ftx_print_char(img, cursor, color, str[-1]);
			cursor = sf_cursor_move_right(cursor, 6, img->size.x, 1);
		}
		else if (str[-1] == '\t')
			cursor = sf_cursor_move_right(cursor, 12, img->size.x, 1);
		else if (str[-1] == '\n' || ((str[-1] == '\r') ^ (str[0] == '\n')))
			cursor = ft_point(1, cursor.y + CRSIZE);
		else
			cursor = sf_cursor_move_right(cursor, 6, img->size.x, 1);
}

void	ftx_clear_img(t_image *img)
{
	int x;
	int y;
	int t;

	if (img == NULL)
		return ;
	y = -img->size.x;
	t = (img->size.x - 1) * img->size.y;
	while ((y += img->size.x) < t)
	{
		x = -1;
		while (++x < img->size.x)
			img->data[y + x] = 0;
	}
}

int	ftx_update(void *ptr)
{
	t_mlx_data		*data;
	t_window		*tmpwin;
	t_image			*tmpimg;
	struct timespec	time;
	int				f;

	data = (t_mlx_data*)ptr;
	clock_gettime(CLOCK_REALTIME, &time);
	tmpwin = data->windows;
	while (tmpwin != NULL)
	{
		f = time.tv_nsec / (1 + 1000000000L / tmpwin->wfps);
		if (f != tmpwin->last_frame || time.tv_sec != tmpwin->last_time.tv_sec)
		{
			if (time.tv_sec != tmpwin->last_time.tv_sec)
			{
				tmpwin->fps = tmpwin->frames;
				tmpwin->frameloss += (tmpwin->frames < tmpwin->wfps);
				tmpwin->frames = 1;
			}
			else
				tmpwin->frames++;
			tmpwin->last_frame = f;
			tmpwin->last_time = time;
			ftx_clear_img(tmpwin->vbuffer);
			if (tmpwin->up_func)
				tmpwin->up_func(tmpwin);
			tmpimg = tmpwin->images;
			while (tmpimg != NULL)
			{
				if (tmpimg->fill_func)
					tmpimg->fill_func(tmpwin, tmpimg);
				if (tmpimg->update && !(tmpimg->update = 0))
					ftx_put_img_to_img(tmpwin->vbuffer, tmpimg, 0);
				tmpimg = tmpimg->next;
			}
			mlx_put_image_to_window(data->mlx, tmpwin->win,
				tmpwin->vbuffer->ptr, tmpwin->vbuffer->pos.x,
				tmpwin->vbuffer->pos.y);
		}
		tmpwin = tmpwin->next;
	}
	return (0);
}

/*
int	ftx_update(void *ptr)
{
	static int				frames = 0;
	static int				frameloss = 0;
	static int				last_frame = 0;
	static struct timespec	last_time = {.tv_sec = 0, .tv_nsec = 0};
	t_mlx_data				*data;
	struct timespec			time;
//	void					*tp;
	long					l;
	t_window				*window;

	if ((data = (t_mlx_data*)ptr)->focused_window != 1)
		return (0);
	if ((window = ftx_get_window(data->focused_window)) == NULL)
		return (0);
	clock_gettime(CLOCK_REALTIME, &time);
	l = time.tv_nsec / (1 + 1000000000L / window->wfps);
	if (l != last_frame || time.tv_sec != last_time.tv_sec)
	{
		window->wfps += (data->keymap[KEY_PLUS] && window->wfps < 600)
					- (data->keymap[KEY_MINUS] && window->wfps > 1);
		window->vbuffer->pos = ft_ptadd(window->vbuffer->pos, ft_point(SPEED
			* (data->keymap[KEY_RIGHT] - data->keymap[KEY_LEFT]), SPEED
			* (data->keymap[KEY_DOWN] - data->keymap[KEY_UP])));
		if (data->mice.map[1])
		{
			window->vbuffer->pos = ft_ptadd(window->vbuffer->pos,
								ft_ptsub(data->mice.pos, data->mice.drag));
			data->mice.drag = data->mice.pos;
		}
		if (time.tv_sec != last_time.tv_sec)
		{
			window->fps = frames;
			frameloss += (frames < window->wfps);
			frames = 1;
		}
		else
			++frames;
		last_frame = l;
		last_time = time;
		mlx_clear_window(data->mlx, window->win);
		sf_draw_scene(data, window->vbuffer);
		//test(data->mlx, window->vbuffer, ft_point(1, 1), WHITE);
		ftx_print_str(window->vbuffer, ft_point(1, 1), WHITE, "What a nice string\nit is with tabs\t returns and shit!awyfvhrvgfbbdsghjdxbvrsejkgergkfdkgncxjbvb gnmhmytojmopyu,tki,tkppjkdsojehui1234325467658754u77!@&$^*$U*(*U%#O)\nPROUT");
//		ftx_print_char(window->vbuffer, ft_point(1, 1), WHITE, 64);
		mlx_put_image_to_window(data->mlx, window->win, window->vbuffer->ptr,
								window->vbuffer->pos.x, window->vbuffer->pos.y);
		//mlx_string_put(data->mlx, window->win, 1, 10, WHITE,
//													tp = ft_itoa(window->fps));
		//free(tp);
		//mlx_string_put(data->mlx, window->win, 1, 25, WHITE,
//													tp = ft_itoa(frameloss));
		//free(tp);
		//mlx_string_put(data->mlx, window->win, 1, 40, WHITE, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.;:<>\'\"!@#$%%^&*()");
		//mlx_string_put(data->mlx, window->win, 1, 55, WHITE, "-_+=[]{}/\\?`~|àãáäâèẽëéêùüũûúòõôóöìïíîĩÀÃÄÁÂÈËÉÊẼÙŨÜÚÛÌĨÏÍÎÒÕÖÓÔ");
	}
	return (0);
}
*/

////////////////////////////////////////////////////////////////////////////////

int	sf_motion(int x, int y, void *p)
{
	t_mlx_data	*data;
	t_window	*window;

	data = ftx_data(GDX_ACCES);
	window = (t_window*)p;
	if (window->id == data->focused_window)
	{
		ft_putnbr(window->id);
		ft_putstr(" - Motion: ");
		if (x >= 0 && x < window->size.x && y >= 0 && y < window->size.y)
		{
			ft_putnbr(x);
			ft_putstr(" ");
			ft_putnbr(y);
			ft_putchar('\n');
			data->mice.pos = ft_point(x, y);
		}
		else
			ft_putstr("OUT OF BOUNDS\n");
	}
	return (0);
}

int	sf_keypress(int key, void *p)
{
	t_mlx_data	*data;

	data = ftx_data(GDX_ACCES);
	ft_putnbr(((t_window*)p)->id);
	ft_putstr(" - Keypress: ");
	ft_putnbr(key);
	ft_putchar('\n');
	if (key == KEY_EXIT)
	{
		ftx_data(GDX_FREE);
		exit(0);
	}
	data->keymap[key] = 1;
	return (0);
}

int	sf_keyrelease(int key, void *p)
{
	t_mlx_data	*data;

	data = ftx_data(GDX_ACCES);
	ft_putnbr(((t_window*)p)->id);
	ft_putstr(" - Keyrelease: ");
	ft_putnbr(key);
	ft_putchar('\n');
	data->keymap[key] = 0;
	return (0);
}

int	sf_buttonpress(int key, int x, int y, void *p)
{
	t_mlx_data	*data;
	t_window	*window;

	data = ftx_data(GDX_ACCES);
	window = (t_window*)p;
	if (x >= 0 && x < window->size.x && y >= 0 && y < window->size.y)
	{
		ft_putnbr(window->id);
		data->focused_window = window->id;
		ft_putstr(" - Buttonpress: ");
		ft_putnbr(key);
		ft_putchar('\n');
		data->mice.map[key] = 1;
		if (key == 1)
			data->mice.drag = ft_point(x, y);
		sf_motion(x, y, p);
	}
	return (0);
}

int	sf_buttonrelease(int key, int x, int y, void *p)
{
	t_mlx_data	*data;
	t_window	*window;

	data = ftx_data(GDX_ACCES);
	window = (t_window*)p;
	ft_putnbr(window->id);
	ft_putstr(" - Buttonrelease: ");
	ft_putnbr(key);
	ft_putchar('\n');
	data->mice.map[key] = 0;
	sf_motion(x, y, p);
	return (0);
}

void	sf_fill_image(t_image *img)
{
	int x;
	int y;
	int w;
	int h;
	int color;

	w = img->size.x;
	h = img->size.y;
	x = w;
	while (--x)
	{
		y = img->size.y;
		while (--y)
		{
			color = (x * 255) / w + ((((w - x) * 255) / w) << 16)
										+ (((y * 255) / h) << 8);
			ftx_putpixelimg(img, ft_point(x, y), color);
		}
	}
}

/*
void	sf_draw_scene(t_mlx_data *data, t_image *img)
{
	t_point	i;
	t_point	start;
	t_point end;
	t_point	size;
	int		***map;

	map = data->map;
	size = data->size;
	i.y = -1;
	while (++i.y < size.y && (i.x = -1))
	{
		while (++i.x < size.x)
		{
			start = ft_point(i.x * SPX + 5 + ZMX * map[i.y][i.x][0], i.y * SPY
								+ 5 + ZMY * map[i.y][i.x][0]);
			if (i.x < size.x - 1)
			{
				end = ft_point((i.x + 1) * SPX + 5 + ZMX * map[i.y][i.x + 1][0],
									i.y * SPY + 5 + ZMY * map[i.y][i.x + 1][0]);
				ftx_line(img, start, end, ft_point(map[i.y][i.x][1], map[i.y][i.x + 1][1]));
			}
			if (i.y < size.y - 1)
			{
				end = ft_point(i.x * SPX + 5 + ZMX * map[i.y + 1][i.x][0],
							(i.y + 1) * SPY + 5 + ZMY * map[i.y + 1][i.x][0]);
				ftx_line(img, start, end, ft_point(map[i.y][i.x][1], map[i.y + 1][i.x][1]));
			}
		}
	}
	ftx_line(img, ft_point(-10, 50), ft_point(50, -10), ft_point(0xFFFFFF, 0x000000));
	ftx_horizontal_line(img, ft_point(0, 250), ft_point(500, 250),ft_point(0x00FF00,
																0xFF0000));
	ftx_vertical_line(img, ft_point(250, 0), ft_point(250, 500), ft_point(0x00FF00,
																0xFF0000));
}
*/

void	init_mlx_data()
{
	t_mlx_data	*data;

	data = ftx_data(GDX_ACCES);
	ft_bzero((void*)data->keymap, sizeof(int) * KEYMAPSIZE);
	ft_bzero((void*)data->mice.map, sizeof(int) * 10);
	data->mlx = mlx_init();
	data->windows = NULL;
	data->focused_window = 0;
	data->update = 0;
	mlx_do_key_autorepeatoff(data->mlx);
}

t_image	*ftx_new_image(t_point size)
{
	t_image	*img;
	void	*mlx;
	int		error;

	if ((img = (t_image*)ft_memalloc(sizeof(t_image))) == NULL)
		return (NULL);
	img->size = size;
	error = !ftx_data(GDX_ACCES) || !(mlx = ftx_data(GDX_ACCES)->mlx);
	error = error || !(img->ptr = mlx_new_image(mlx, size.x, size.y));
	error = error || !(img->data = (int *)mlx_get_data_addr(img->ptr,
		&(img->bpp), &(img->size_line), &(img->endian)));
	if (error)
	{
		if (img->ptr)
			mlx_destroy_image(mlx, img->ptr);
		ft_memdel((void**)img);
	}
	return (img);
}

/*
** return 0 on succes, 1 if img is NULL ans -1 if mlx can't be loaded
*/

int		ftx_free_image(t_image *img)
{
	void	*mlx;

	if (!ftx_data(GDX_ACCES) || !(mlx = ftx_data(GDX_ACCES)->mlx))
		return (-1);
	if (img == NULL)
		return (1);
	if (img->ptr)
		mlx_destroy_image(mlx, img->ptr);
	if (img->next)
	{
		if (img->prev)
		{
			img->prev->next = img->next;
			img->next->prev = img->prev;
		}
		else
			img->next->prev = NULL;
	}
	else
		if (img->prev)
			img->prev->next = NULL;
	free(img);
	return (0);
}

/*
** same returns has ftx_free_image, any image of the chain can be used to start
*/

int		ftx_free_all_images(t_image *img)
{
	void	*mlx;
	t_image	*tmp;

	if (!ftx_data(GDX_ACCES) || !(mlx = ftx_data(GDX_ACCES)->mlx))
		return (-1);
	if (img == NULL)
		return (1);
	while (img->next)
		img = img->next;
	tmp = img;
	while (tmp)
	{
		tmp = img->prev;
		if (img->ptr)
			mlx_destroy_image(mlx, img->ptr);
		free(img);
	}
	return (0);
}

int		ftx_free_all_windows(t_window *win)
{
	void		*mlx;
	t_window	*tmp;

	if (!ftx_data(GDX_ACCES) || !(mlx = ftx_data(GDX_ACCES)->mlx))
		return (-1);
	if (win == NULL)
		return (1);
	while (win->next)
		win = win->next;
	tmp = win;
	while (tmp)
	{
		tmp = win->prev;
		if (win->win)
			mlx_destroy_window(mlx, win->win);
		if (win->vbuffer)
			ftx_free_image(win->vbuffer);
		if (win->images)
			ftx_free_all_images(win->images);
		free(win);
	}
	return (0);
}

int		ftx_free_window(t_window *win)
{
	void	*mlx;

	if (!ftx_data(GDX_ACCES) || !(mlx = ftx_data(GDX_ACCES)->mlx))
		return (-1);
	if (win == NULL)
		return (1);
	(void)(win->win && mlx_destroy_window(mlx, win->win));
	(void)(win->vbuffer && ftx_free_image(win->vbuffer));
	if (win->images)
		ftx_free_all_images(win->images);
	if (win->next)
	{
		if (win->prev)
		{
			win->prev->next = win->next;
			win->next->prev = win->prev;
		}
		else
			win->next->prev = NULL;
	}
	else
		if (win->prev)
			win->prev->next = NULL;
	free(win);
	return (0);
}

t_window	*ftx_new_window(t_point size, char *name, int wfps)
{
	t_window	*window;
	void		*mlx;
	int			error;

	if ((window = (t_window*)ft_memalloc(sizeof(t_window))) == NULL)
		return (NULL);
	error = !ftx_data(GDX_ACCES) || !(mlx = ftx_data(GDX_ACCES)->mlx);
	error = error || !(window->win = mlx_new_window(mlx, size.x, size.y, name));
	if (!error)
		window->size = size;
	error = error || !(window->vbuffer = ftx_new_image(size));
	if (!error)
	{
		window->wfps = wfps;
		window->zoom = 1;
	}
	else
	{
		if (window->win)
			mlx_destroy_window(mlx, window->win);
		if (window->vbuffer)
			ftx_free_image(window->vbuffer);
		ft_memdel((void**)window);
	}
	return (window);
}

int		ftx_add_window(t_window *win)
{
	t_mlx_data	*data;
	t_window	*tmp;
	static int	gid = 0;

	data = ftx_data(GDX_ACCES);
	++gid;
	win->id = gid;
	if (data->windows == NULL)
		data->windows = win;
	else
	{
		tmp = data->windows;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = win;
	}
	return (gid);
}

void	ftx_add_image(t_window *win, t_image *img, int id)
{
	t_image		*tmp;

	img->id = id;
	if (win->images == NULL)
		win->images = img;
	else
	{
		tmp = win->images;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = img;
	}
}

int		fill_fdf(t_window *win, t_image *img)
{
	t_fdf		*fdf;
	t_mlx_data	*data;
	t_point3d	tmp;
	t_point		pos;

//	sf_draw_scene(ftx_data(GDX_ACCES), img);
	data = ftx_data(GDX_ACCES);
	if (data ->focused_window == win->id)
	{
		fdf = (t_fdf*)(win->data);
		if (data->keymap[KEY_CTRL_LEFT])
			win->zoom += data->keymap[KEY_PAD_PLUS] - data->keymap[KEY_PAD_MINUS];
		if (data->keymap[KEY_X])
		{
			fdf->rotation->r.x += 0.05 * (data->keymap[KEY_PAD_PLUS] - data->keymap[KEY_PAD_MINUS]);
			fdf->rotation->r.x = data->keymap[KEY_PAD_0] ? 0 : fdf->rotation->r.x;
		}
		if (data->keymap[KEY_Y])
		{
			fdf->rotation->r.y += 0.05 * (data->keymap[KEY_PAD_PLUS] - data->keymap[KEY_PAD_MINUS]);
			fdf->rotation->r.y = data->keymap[KEY_PAD_0] ? 0 : fdf->rotation->r.y;
		}
		if (data->keymap[KEY_Z])
		{
			fdf->rotation->r.z += 0.05 * (data->keymap[KEY_PAD_PLUS] - data->keymap[KEY_PAD_MINUS]);
			fdf->rotation->r.z = data->keymap[KEY_PAD_0] ? 0 : fdf->rotation->r.z;
		}
		ft_update_rotation_matrix(fdf->rotation);
		pos.y = -1;
		while (++pos.y < fdf->size.y && (pos.x = -1))
			while (++pos.x < fdf->size.x)
			{
				tmp = ft_matmultvect(fdf->rotation, fdf->map3[pos.y][pos.x], fdf->camera_pos);
				tmp = ft_pt3add(tmp, fdf->camera_pos);
				fdf->map2[pos.y][pos.x] = ft_3d_to_2d((t_point3d){0, 0, 50}, ft_point(win->size.x / 2, win->size.y / 2), tmp, win->zoom);
			}
		pos.y = -1;
		ftx_clear_img(img);
		while (++pos.y < fdf->size.y && (pos.x = -1))
			while (++pos.x < fdf->size.x)
			{
				if (pos.x < fdf->size.x - 1)
					ftx_line(img, fdf->map2[pos.y][pos.x], fdf->map2[pos.y][pos.x + 1], ft_point(fdf->map[pos.y][pos.x][1], fdf->map[pos.y][pos.x + 1][1]));
				if (pos.y < fdf->size.y - 1)
					ftx_line(img, fdf->map2[pos.y][pos.x], fdf->map2[pos.y + 1][pos.x], ft_point(fdf->map[pos.y][pos.x][1], fdf->map[pos.y + 1][pos.x][1]));
			}
		img->update = 1;
	}
	return (0);
}

int		fill_info(t_window *win, t_image *img)
{
	void *tmp;

	ftx_clear_img(img);
	ftx_print_str(img, ft_point(1, 1), WHITE, tmp = ft_itoa(win->fps));
	img->update = 1;
	free(tmp);
	return (0);
}

int		up_fdf(t_window *win)
{
	(void)win;
	return (0);
}

void	main_window_init(int ***map, t_point size)
{
	t_window	*window;
	t_image		*image;
	t_fdf		*fdf;
	int			i;
	int			j;

	window = ftx_new_window(ft_point(1000, 1000), "fdf", 60);
	image = ftx_new_image(ft_point(1000, 1000));
	image->fill_func = fill_fdf;
	ftx_add_image(window, image, 1);
	(image = ftx_new_image(ft_point(200, 100)))->fill_func = fill_info;
	ftx_add_image(window, image, 2);
	window->up_func = up_fdf;
	fdf = (t_fdf*)ft_memalloc(sizeof(t_fdf));
	fdf->map = map;
	fdf->size = size;
	fdf->map3 = (t_point3d**)ft_memalloc(sizeof(t_point3d*) * size.y);
	fdf->map2 = (t_point**)ft_memalloc(sizeof(t_point*) * size.y);
	i = -1;
	while (++i < size.y)
	{
		fdf->map3[i] = (t_point3d*)ft_memalloc(sizeof(t_point3d) * size.x);
		fdf->map2[i] = (t_point*)ft_memalloc(sizeof(t_point) * size.x);
		j = -1;
		while (++j < size.x)
			fdf->map3[i][j] = (t_point3d){j, i, map[i][j][0]};
	}
	fdf->rotation = (t_mat_r*)ft_memalloc(sizeof(t_mat_r));
	fdf->eye = (t_point3d){0, 0, 7};
	window->data = (void*)fdf;
	window->use_code = C_FDF;
	ftx_add_window(window);
	ft_putnbr(window->id);
	ft_putchar('\n');
	mlx_hook(window->win, 2, (1L << 0), sf_keypress, window);
	mlx_hook(window->win, 3, (1L << 1), sf_keyrelease, window);
	mlx_hook(window->win, 4, (1L << 2), sf_buttonpress, window);
	mlx_hook(window->win, 5, (1L << 3), sf_buttonrelease, window);
	mlx_hook(window->win, 6, (1L << 6), sf_motion, window);
}

void	term_window_init()
{
	t_window	*window;

	window = ftx_new_window(ft_point(500, 500), "term", 30);
	window->use_code = C_TERM;
	ftx_add_window(window);
	mlx_hook(window->win, 2, (1L << 0), sf_keypress, window);
	mlx_hook(window->win, 3, (1L << 1), sf_keyrelease, window);
	mlx_hook(window->win, 4, (1L << 2), sf_buttonpress, window);
	mlx_hook(window->win, 5, (1L << 3), sf_buttonrelease, window);
	mlx_hook(window->win, 6, (1L << 6), sf_motion, window);
}

void	button_window_init()
{
	t_window	*window;

	window = ftx_new_window(ft_point(500, 500), "button", 10);
	window->use_code = C_BUTTON;
	ftx_add_window(window);
	mlx_hook(window->win, 2, (1L << 0), sf_keypress, window);
	mlx_hook(window->win, 3, (1L << 1), sf_keyrelease, window);
	mlx_hook(window->win, 4, (1L << 2), sf_buttonpress, window);
	mlx_hook(window->win, 5, (1L << 3), sf_buttonrelease, window);
	mlx_hook(window->win, 6, (1L << 6), sf_motion, window);
}

void	fdf(int ***map, t_point size)
{
	t_mlx_data	*data;

	if ((data = ftx_data(GDX_NEW)) == NULL)
		return ;
	init_mlx_data();
	main_window_init(map, size);
	term_window_init();
	button_window_init();
	mlx_loop_hook(data->mlx, ftx_update, (void*)data);
	mlx_loop(data->mlx);
}

t_point	fdf_parse_file0(char *filename)
{
	int		fd;
	char	*line;
	t_point	t;

	if ((fd = open(filename, O_RDONLY)) < 0)
		return ((t_point){.x = -1, .y = -1});
	t = ft_point(-1, 0);
	while (get_next_line(fd, &line) == 1 && !(0 * ++t.y))
		if (t.x == -1)
			t.x = ft_strcntw(line);
		else if (t.x != ft_strcntw(line))
			return ((t_point){.x = -1, .y = -1});
	close(fd);
	return (t);
}

int		***fdf_parse_file(int fd, t_point t)
{
	char	*line;
	char	*tmp;
	t_point	i;
	int		***map;

	map = (int ***)ft_tab3dalloc(t.x, t.y, 2, sizeof(int));
	i.y = -1;
	while (get_next_line(fd, &line) == 1 && !(0 * ++i.y))
	{
		tmp = line;
		i.x = 0;
		map[i.y][i.x][0] = ft_atoi(tmp);
		if (ft_strchr(tmp, ',') != NULL &&
				ft_strchr(tmp, ',') < ft_strnw(tmp))
			map[i.y][i.x][1] = ft_atoi(ft_strchr(tmp, ',') + 1);
		else
			map[i.y][i.x][1] = 0x00FFFF;
		while ((tmp = ft_strnw(tmp))[0] != 0 && !(0 * ++i.x))
		{
			map[i.y][i.x][0] = ft_atoi(tmp);
			if (ft_strchr(tmp, ',') != NULL &&
				ft_strchr(tmp, ',') < ft_strnw(tmp))
				map[i.y][i.x][1] = ft_atoi(ft_strchr(tmp, ',') + 1);
			else
				map[i.y][i.x][1] = 0x00FFFF;
		}
		free(line);
	}
	return (map);
}

int		main(int argc, char **argv)
{
	int		***map;
	t_point	t;
	int		fd;


//	fd = -1;
//	printf("tab: %d\n",'\t');
//	while (++fd < 95)
//	{
//		test2(g[fd]);
//		ft_putstr(",\n");
//	}
	if (argc < 2)
	{
		write(1, "Usage: ", 7);
		write(1, argv[0], ft_strlen(argv[0]));
		write(1, " <filename> [arguments]\n", 25);
		return (0);
	}
	t = fdf_parse_file0(argv[1]);
	if (t.y == -1)
		return (0);
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return (0);
	map = fdf_parse_file(fd, t);
	close(fd);
	fdf(map, t);
	return (0);
}

/*
int	main(void)
{
	void *mlx;
	void *win;
	t_window *window;
	t_mlx_data	*data;

	data = ftx_data(GDX_NEW);
	init_mlx_data(NULL, ft_point(0, 0));
	mlx = data->mlx;
	win = mlx_new_window(mlx, 500, 500, "fdf");
	window = ftx_new_window(ft_point(500, 500), win, 60);
	data->windows = window;
	//ftx_add_window(window);
	mlx_hook(win, 2, (1L << 0), sf_keypress, NULL);
	win = mlx_new_window(mlx, 500, 500, "term");
//
	window = ftx_new_window(ft_point(500, 500), win, 10);
//	data->windows->next = window;
	mlx_hook(win, 2, (1L << 0), sf_keypress, NULL);
	mlx_loop(mlx);
}
*/

/*
int	main(void)
{
	printf("%X\ntest: %d\n",*(int *)(char [4]){0xAA, 0xBB, 0xCC, 0xDD}, (((*(int *)(char [4]){0xAA, 0xBB, 0xCC, 0xDD}) & 0xFF) == 0xAA));
	printf("little endian: %d\t big endian: %d\t local endian: %d\n", __ORDER_LITTLE_ENDIAN__, __ORDER_BIG_ENDIAN__, __BYTE_ORDER__);

	return (0);
}
*/

/*
int	main(void)
{
	t_point3d test1 = (t_point3d){1, 0, 0};
	t_point3d test2 = (t_point3d){1, 0, 0};
	t_point3d test3;
	t_mat_3_3 test4;
	test4 = ft_rotation_matrix(0, RADIAN(45), 0);
	test3 = ft_matmultvect(test4, test1, test2);
	printf("%f, %f, %f\n", test4.m[0][0], test4.m[0][1], test4.m[0][2]);
	printf("%f, %f, %f\n", test4.m[1][0], test4.m[1][1], test4.m[1][2]);
	printf("%f, %f, %f\n", test4.m[2][0], test4.m[2][1], test4.m[2][2]);
	printf("%f, %f, %f\n", test3.x, test3.y, test3.z);
}
*/
