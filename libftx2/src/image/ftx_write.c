/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_write.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 08:43:44 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/25 21:25:38 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <libftx.h>

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

static int		sf_print_char(t_image *img, t_point *pos, int color, char c)
{
	int			x;
	int			y;
	int64_t		mask;
	int64_t		tmp;
	int			move;

	if (c == '\n')
	{
		*pos = ft_point(1, pos->y + 10);
		return (pos->y + 10 < img->size.y);
	}
	y = -1;
	mask = 1;
	move = (c == '\t') ? 24 : 6;
	tmp = sf_code_to_ascii(c);
	while (++y < 11 && (x = -1))
		while (++x < 5)
			if (tmp & ((mask << (4 - x)) << 5 * (10 - y)))
				ftx_put_pixel_img(img, pos->x + x, pos->y + y, color);
	if (pos->x + move > img->size.x - 1)
		*pos = ft_point(img->size.x + 1, pos->y + 10);
	else
		pos->x += move;
	return (pos->y + 10 < img->size.y);
}

size_t			ftx_write(t_image *img, char *str, size_t count, int color)
{
	size_t	out;

	if (img == NULL || (str == NULL && count > 0))
		return (-1 + 0 * ft_error(EINVAL, "ftx_write got NULL parameter\n"));
	out = 0;
	while (count-- && ++out && sf_print_char(img, &img->cursor, color, *str++))
		;
	return (out);
}
