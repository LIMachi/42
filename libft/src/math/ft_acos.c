/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_acos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 13:23:27 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/18 23:46:33 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#if defined(_MATH_H) && _MATH_H == 1

double	ft_acos(double x)
{
	return (acos(x));
}

#else

/*
** low precision acos (around 5th digit of frac)
*/

double	ft_acos(double x)
{
	double n;
	double out;

	n = x < 0;
	x = ABS(x);
	out = -0.0187293;
	out *= x;
	out += 0.0742610;
	out *= x;
	out -= 0.2121144;
	out *= x;
	out += 1.5707288;
	out *= ft_sqrtd(1.0 - x);
	out -= 2 * n * out;
	return (n * M_PI + out);
}

#endif
