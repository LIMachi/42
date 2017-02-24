/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_holder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 17:02:04 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/25 17:02:36 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_textures_holder	*textures_holder(void)
{
	static t_textures_holder	th = {.nb_info = 0, .path = NULL,

	.info = NULL, .total_raw_size = 0, .raw_bmp = NULL};
	return (&th);
}
