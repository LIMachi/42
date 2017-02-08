/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 13:14:16 by pbondoer          #+#    #+#             */
/*   Updated: 2017/01/30 15:21:20 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_ubmp	*out(void)
{
	static t_ubmp		out = {.size = {.x = 0, .y = 0}, .data = NULL};

	return (&out);
}

t_ubmp	*prim_map(void)
{
	static t_ubmp		out = {.size = {.x = 0, .y = 0}, .data = NULL};

	return (&out);
}
