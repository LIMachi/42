/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 19:22:28 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/21 20:29:28 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <libftx.h>
#include <fractol.h>

size_t	print_float_3_8(t_image *img, float f, int color)
{
	char	buff[8];
	size_t	out;

	if (f > 999.999999f || f < -999.999999f)
		return (ftx_write(img, "invalid", 7, color));
	out = 0;
	if (f < 0.0f)
	{
		out += ftx_write(img, "-", 1, color);
		f = -f;
	}
	buff[0] = '0' + (int)ft_modf(f / 100.0f, 10.0f);
	buff[1] = '0' + (int)ft_modf(f / 10.0f, 10.0f);
	buff[2] = '0' + (int)ft_modf(f, 10.0f);
	buff[3] = '.';
	buff[4] = '0' + (int)ft_modf(f * 10.0f, 10.0f);
	buff[5] = '0' + (int)ft_modf(f * 100.0f, 10.0f);
	buff[6] = '0' + (int)ft_modf(f * 1000.0f, 10.0f);
	buff[7] = '0' + (int)ft_modf(f * 10000.0f, 10.0f);
	return (out + ftx_write(img, buff, 8, color));
}

size_t	print_complex_3_8(t_image *img, t_cl_comp c, int color)
{
	size_t	out;

	out = print_float_3_8(img, c.r, color);
	out += ftx_write(img, " + ", 3, color);
	out += print_float_3_8(img, c.i, color);
	out += ftx_write(img, "i", 1, color);
	return (out);
}

void	print_info(t_fractol_data *data, t_image *img)
{
	char	buff[4];

	ftx_write(ftx_set_cursor(img, 1, 1), "iterations: ", 12, 0xFFFFFF);
	buff[0] = ('0' + (data->args.iterations / 1000) % 10);
	buff[1] = ('0' + (data->args.iterations / 100) % 10);
	buff[2] = ('0' + (data->args.iterations / 10) % 10);
	buff[3] = ('0' + data->args.iterations % 10);
	ftx_write(img, buff, 4, 0xFFFFFF);
	ftx_write(img, "\nlock: ", 7, 0xFFFFFF);
	ftx_write(img, data->lock ? "on \nz0: " : "off\nz0: ", 8, 0xFFFFFF);
	print_complex_3_8(img, data->args.z0, 0xFFFFFF);
	ftx_write(img, "\nup left corner: ", 17, 0xFFFFFF);
	print_complex_3_8(img, data->args.vp_ul, 0xFFFFFF);
	ftx_write(img, "\ndown right corner: ", 20, 0xFFFFFF);
	print_complex_3_8(img, data->args.vp_dr, 0xFFFFFF);
	ftx_write(img, "\ncolor shift: ", 14, 0xFFFFFF);
	print_float_3_8(img, data->args.color, 0xFFFFFF);
}
