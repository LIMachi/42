/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_uint128.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 06:53:13 by hmartzol          #+#    #+#             */
/*   Updated: 2017/03/16 01:18:20 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <ft_int.h>

__uint128_t	cast_uint128(__uint128_t v, int tlength)
{
	if (tlength && tlength <= 8)
		return (v & (0xFFFFFFFFFFFFFFFF >> (64 - (tlength << 3))));
	return (v);
}
