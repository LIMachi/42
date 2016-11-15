/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrtd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 0000/00/00 00:00:00 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/20 15:34:21 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

double			ft_sqrtd(double v)
{
	double	t[3];
	double	out;
	int		i;
	double	j;

	out = 0.0;
	j = 1.0;
	t[2] = SIGN(v);
	v = ABS(v);
	i = DOUBLE_PRECISION + 1;
	while (--i >= -DOUBLE_PRECISION)
	{
		t[0] = ft_pow10d(i);
		t[1] = j * t[0];
		if (((2.0 * out) + t[1]) * t[1] < v)
		{
			while ((j < 10) && ((2.0 * out) + t[1]) * t[1] < v)
				t[1] = t[0] * ++j;
			t[1] = t[0] * --j;
			v -= ((2.0 * out) + t[1]) * t[1];
			out += t[1];
			j = 1.0;
		}
	}
	return (t[2] * out);
}
