/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_multiply.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 16:23:28 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/14 08:42:06 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int		ftx_color_multiply(int color, double mult)
{
	double red;
	double green;
	double blue;

	red = (double)((color & 0x00FF0000) >> 16);
	green = (double)((color & 0x0000FF00) >> 8);
	blue = (double)(color & 0x000000FF);
	red = MIN(red * mult, 255.0);
	green = MIN(green * mult, 255.0);
	blue = MIN(blue * mult, 255.0);
	return ((color & 0xFF000000) | (((int)red) << 16) | (((int)green) << 8) |
															(int)blue);
}
