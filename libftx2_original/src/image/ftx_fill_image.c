/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_fill_image.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 14:51:21 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/21 17:08:55 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <libftx.h>

t_image	*ftx_fill_image(t_image *img, const int color, const double value)
{
	t_point	pos;

	pos.y = -1;
	while (++pos.y < img->size.y && (pos.x = -1))
		while (++pos.x < img->size.x)
			ftx_slerp_pixel(img, pos, color, value);
	return (img);
}
