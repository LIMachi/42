/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrti.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 0000/00/00 00:00:00 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/06 22:10:07 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int				ft_sqrti(int v)
{
	int	out;
	int s;

	if (v >= -1 && v <= 1)
		return (v);
	out = 0;
	s = SIGN(v);
	v = ABS(v);
	while (out * out < v)
		++out;
	return (s * (out * out > v ? out - 1 : out));
}
