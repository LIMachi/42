/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 13:06:31 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/24 21:49:23 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#if defined(_MATH_H) && _MATH_H == 1

double	ft_sin(double x)
{
	return (sin(x));
}

#else

double	ft_sin(double x)
{
	double	out;
	double	t;

	while (x > M_PI)
		x -= 2 * M_PI;
	while (x < -M_PI)
		x += 2 * M_PI;
	out = x;
	x *= x;
	out -= (t = out * x) / 6.0;
	out += (t *= x) / 120.0;
	out -= (t *= x) / 5040.0;
	out += (t *= x) / 362880.0;
	out -= (t *= x) / 39916800.0;
	return (out + (t * x) / 6227020800.0);
}

#endif
