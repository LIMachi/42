/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bswap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/15 08:31:33 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/07 04:16:24 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

unsigned long long int	ft_bswap64(unsigned long long int x)
{
	if (ASM && BSWAPA)
	{
		__asm__("bswap %q0" : "=r" (x) : "0" (x));
		return (x);
	}
	return (((x & 0xFF00000000000000ull) >> 56)
			| ((x & 0xFF000000000000ull) >> 40)
			| ((x & 0xFF0000000000ull) >> 24) | ((x & 0xFF00000000ull) >> 8)
			| ((x & 0xFF000000ull) << 8) | ((x & 0xFF0000ull) << 24)
			| ((x & 0xFF00ull) << 40) | ((x & 0xFFull) << 56));
}

unsigned long int	ft_bswap32(unsigned long int x)
{
	if (ASM == 1)
	{
		if (BSWAPA)
			__asm__("bswap %0" : "=r" (x) : "0" (x));
		else
			__asm__ ("rorw $8, %w0;" "rorl $16, %0;" "rorw $8, %w0" : "=r" (x) \
					: "0" (x) : "cc");
		return (x);
	}
	return (((x & 0xFF000000) >> 24) | ((x & 0xFF0000) >> 8)
			| ((x & 0xFF00) << 8) | ((x & 0xFF) << 24));
}

unsigned short int	ft_bswap16(unsigned short int x)
{
	if (ASM == 1)
	{
		__asm__ ("rorw $8, %w0" : "=r" (x) : "0" (x) : "cc");
		return (x);
	}
	return (((x & 0xFF00) >> 8) | ((x & 0xFF) << 8));
}
