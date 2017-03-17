/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_uint128.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 06:53:13 by hmartzol          #+#    #+#             */
/*   Updated: 2017/03/17 03:30:29 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <ft_int.h>

__uint128_t	cast_uint128(__uint128_t v, int blength, int sign)
{
	static const __uint128_t m = (((__uint128_t)0xFFFFFFFFFFFFFFFFull) << 64) |

	0xFFFFFFFFFFFFFFFFull;
	if (blength <= 0)
		return (0);
	if (blength > 127)
		return (v);
	v &= m >> (128 - blength);
	if (sign && v & (__uint128_t)1 << (blength - 1))
		v |= m << blength;
	return (v);
}
