/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quat_inverse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 0000/00/00 00:00:00 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/06 23:56:29 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_quaternion	ft_quat_inverse(const t_quaternion q)
{
	double	t;

	t = 1 / (q.r * q.r + q.i * q.i + q.j * q.j + q.k * q.k);
	return ((t_quaternion){.r = t * q.r, .i = -t * q.i, .j = -t * q.j,
														.k = -t * q.k});
}
