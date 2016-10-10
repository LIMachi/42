/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrtf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 0000/00/00 00:00:00 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/07 00:31:09 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

float			ft_sqrtf(float v)
{
	float	t[3];
	float	out;
	int		i;
	float	j;

	out = 0.0f;
	j = 1.0f;
	t[2] = SIGN(v);
	v = ABS(v);
	i = FLOAT_PRECISION + 1;
	while (--i >= -FLOAT_PRECISION)
	{
		t[0] = ft_pow10f(i);
		t[1] = j * t[0];
		if (((2.0f * out) + t[1]) * t[1] < v)
		{
			while ((j < 10) && ((2.0f * out) + t[1]) * t[1] < v)
				t[1] = t[0] * ++j;
			t[1] = t[0] * --j;
			v -= ((2.0f * out) + t[1]) * t[1];
			out += t[1];
			j = 1.0f;
		}
	}
	return (t[2] * out);
}
