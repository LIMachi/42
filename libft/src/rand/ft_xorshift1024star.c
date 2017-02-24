/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xorshift1024star.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 08:51:18 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/24 09:38:32 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

unsigned long long	ft_xorshift1024star(void)
{
	int					pos;
	unsigned long long	s0;
	unsigned long long	s1;
	unsigned long long	*s;

	pos = ft_global_xorshift1024star()->p;
	s = ft_global_xorshift1024star()->s;
	s0 = s[pos];
	pos = (pos + 1) & 0xF;
	s1 = s[pos];
	s1 ^= s1 << 31;
	s[pos] = s1 ^ (s1 >> 11) ^ (s0 >> 30);
	ft_global_xorshift1024star()->p = pos;
	return (s[pos] * 1181783497276652981ull);
}
