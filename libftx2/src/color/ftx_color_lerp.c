/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_color_lerp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 17:31:53 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/21 17:08:25 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** will return a color lerp (blending/interpolation), of color front (f) on
** color back (b) with a force (v) contained in [0.0, 1.0] (if v is negative,
** front and back color will be switched, and if v is > 1, it will be truncated
** to 1)
*/

int	ftx_color_lerp(const int f, const int b, double v)
{
	if (v < 0.0)
		v = -v + (double)(int)v;
	if (v > 1.0)
		v = 1.0;
	if (v == 1.0)
		return (f);
	if (v == 0.0)
		return (b);
	return (((int)((double)((f >> 16) & 0xFF) * v +
					(double)((b >> 16) & 0xFF) * (1.0 - v)) << 16) |
			((int)((double)((f >> 8) & 0xFF) * v +
					(double)((b >> 8) & 0xFF) * (1.0 - v)) << 8) |
			((int)((double)(f & 0xFF) * v + (double)(b & 0xFF) * (1.0 - v))));
}
