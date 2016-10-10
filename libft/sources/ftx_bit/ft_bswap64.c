/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bswap64.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/00/00 00:00:00 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/08 08:25:11 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

unsigned long long int	ft_bswap64(const unsigned long long int x)
{
	return (((x & 0xFF00000000000000ull) >> 56)
			| ((x & 0xFF000000000000ull) >> 40)
			| ((x & 0xFF0000000000ull) >> 24) | ((x & 0xFF00000000ull) >> 8)
			| ((x & 0xFF000000ull) << 8) | ((x & 0xFF0000ull) << 24)
			| ((x & 0xFF00ull) << 40) | ((x & 0xFFull) << 56));
}
