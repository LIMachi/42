/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_complex_divide.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 0000/00/00 00:00:00 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/06 23:37:51 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_complex		ft_complex_divide(const t_complex a, const t_complex b)
{
	double	t;
	double	d;

	if (ABS(b.r) >= ABS(b.i))
	{
		t = b.i / b.r;
		d = 1 / (b.r + b.i * t);
		return ((t_complex){.r = (a.r + a.i * t) * d,
							.i = (a.i - a.r * t) * d});
	}
	else
	{
		t = b.r / b.i;
		d = 1 / (b.i + b.r * t);
		return ((t_complex){.r = (a.i + a.r * t) * d,
							.i = (a.r - a.i * t) * d});
	}
}
