/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_complex_power.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 0000/00/00 00:00:00 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/06 23:40:06 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_complex		ft_complex_power(const t_complex c, int power)
{
	t_complex	t;

	if (power == 0)
		return ((t_complex){.r = 1, .i = 0});
	if (power > 0)
	{
		t = c;
		while (--power)
			t = ft_complex_multiply(t, c);
		return (t);
	}
	else
	{
		t = ft_complex_divide((t_complex){.r = 1, .i = 0}, c);
		while (++power)
			t = ft_complex_divide(t, c);
		return (t);
	}
}
