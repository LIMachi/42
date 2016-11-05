/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quat_rotation_to_matrix.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/02 11:33:44 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_matrix				*ft_quat_rotation_to_matrix(t_matrix *mat,
													t_quaternion q)
{
	if (q.r == 0 && q.i == 0 && q.j == 0 && q.k == 0)
		return (mat);
	if (mat == NULL)
		if ((mat = ft_matrix_new(3, 3)) == NULL)
			return (NULL);
	if (ft_quat_norm(q) != 1)
		q = ft_quat_normalize(q);
	mat->mat[0][0] = 1 - 2 * (q.j * q.j + q.k * q.k);
	mat->mat[0][1] = 2 * (q.i * q.j - q.r * q.k);
	mat->mat[0][2] = 2 * (q.r * q.j + q.i * q.k);
	mat->mat[1][0] = 2 * (q.r * q.k + q.i * q.j);
	mat->mat[1][1] = 1 - 2 * (q.i * q.i + q.k * q.k);
	mat->mat[1][2] = 2 * (q.j * q.k - q.r * q.i);
	mat->mat[2][0] = 2 * (q.i * q.k - q.r * q.j);
	mat->mat[2][1] = 2 * (q.r * q.i + q.j * q.k);
	mat->mat[2][2] = 1 - 2 * (q.i * q.i + q.j * q.j);
	return (mat);
}
