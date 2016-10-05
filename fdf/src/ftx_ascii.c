/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_ascii.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/15 08:54:18 by hmartzol          #+#    #+#             */
/*   Updated: 2016/07/16 03:47:17 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftx.h>

static int64_t	sf_code_to_ascii(unsigned char code)
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

static t_point	sf_cursor_move_right(t_point cursor, int movex, int imgx,
									int startx)
{
	if (cursor.x + movex > imgx)
		return (ft_point(startx, cursor.y + CRSIZE));
	cursor.x += movex;
	return cursor;
}

/*
** returns the start of the character - 1 in x, and the width + 2 in y
*/

t_point			ft_get_width(char c)
{
	int		w;
	int		i;
	int64_t	mask;
	int64_t	tmp;
	t_point	out;

	w = 0;
	mask = 0x1F;
	tmp = sf_code_to_ascii(c);
	out = (t_point){-2, -2};
	i = -5;
	while ((i += 5) < 55)
		w |= (tmp & (mask << i)) >> i;
	i = 5;
	while (--i >= 0)
		if (w & (1 << i) && !(w & (1 << (i + 1))) && out.y == -2)
			out.y = 4 - i;
	i = 0;
	while (++i < 5)
		if (w & (1 << i) && !(w & (1 << (i - 1))) && out.x == -2)
			out.x = i;
	if (out.x == -2)
		out.x = 4;
	return (out);
}

void			ftx_print_char(t_image *img, t_point pos, int color, char c)
{
	int 		x;
	int 		y;
	t_mlx_data	*data;
	int64_t		mask;
	int64_t		tmp;
	if ((data = ftx_data(GDX_ACCES)) == NULL)
		return ;
	y = -1;
	mask = 1;
	tmp = sf_code_to_ascii(c);
	while (++y < 11 && (x = -1))
		while (++x < 5)
			if (tmp & ((mask << (4 - x)) << 5 * (10 - y)))
				ftx_putpixelimg(img, ft_ptadd(pos, ft_point(x, y)), color);
}

void			ftx_print_str(t_image *img, t_point pos, int color, char *str)
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
