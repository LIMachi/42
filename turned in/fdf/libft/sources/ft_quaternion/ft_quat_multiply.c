/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quat_multiply.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 0000/00/00 00:00:00 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/06 23:53:02 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_quaternion	ft_quat_multiply(const t_quaternion a, const t_quaternion b)
{
	return ((t_quaternion){
		.r = a.r * b.r - a.i * b.i - a.j * b.j - a.k * b.k,
		.i = a.r * b.i + b.r * a.i + a.j * b.k - b.j * a.k,
		.j = a.r * b.j + b.r * a.j - a.i * b.k + b.i * a.k,
		.k = a.r * b.k + b.r * a.k + a.i * b.j - b.i * a.j});
}
