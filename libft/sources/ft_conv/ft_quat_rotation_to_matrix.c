/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quat_rotation_to_matrix.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/07 01:08:10 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_matrix				*ft_quat_rotation_to_matrix(t_quaternion q)
{
	t_matrix	*out;

	if ((out = ft_matrix_new(3, 3)) == NULL)
		return (NULL);
	if (ft_quat_norm(q) != 1)
		q = ft_quat_normalize(q);
	out->mat[0][0] = 1 - 2 * (q.j * q.j + q.k * q.k);
	out->mat[0][1] = 2 * (q.i * q.j - q.r * q.k);
	out->mat[0][2] = 2 * (q.r * q.j + q.i * q.k);
	out->mat[1][0] = 2 * (q.r * q.k + q.i * q.j);
	out->mat[1][1] = 1 - 2 * (q.i * q.i + q.k * q.k);
	out->mat[1][2] = 2 * (q.j * q.k - q.r * q.i);
	out->mat[2][0] = 2 * (q.i * q.k - q.r * q.j);
	out->mat[2][1] = 2 * (q.r * q.i + q.j * q.k);
	out->mat[2][2] = 1 - 2 * (q.i * q.i + q.j * q.j);
	return (out);
}
