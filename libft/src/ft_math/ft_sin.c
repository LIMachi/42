/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 13:06:31 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/06 22:37:55 by hmartzol         ###   ########.fr       */
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

	while (x > PI)
		x -= 2 * PI;
	while (x < -PI)
		x += 2 * PI;
	out = x;
	x *= x;
	out -= (t = out * x) / 6;
	out += (t *= x) / 120;
	out -= (t *= x) / 5040;
	out += (t *= x) / 362880;
	out -= (t *= x) / 39916800;
	return (out + (t * x) / 6227020800);
}

#endif
