/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_multply_vector.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/07 01:04:04 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** return -1 if pointers where invalid, and -2 if the matrix size wasn't 3 * 3
*/

int				ft_matrix_multply_vector(t_vector *v, t_matrix *m)
{
	if (v == NULL || m == NULL)
		return (-1);
	if (m->size.x != 3 || m->size.y != 3)
		return (-2);
	*v = (t_vector){
		.x = v->x * m->mat[0][0] + v->y * m->mat[0][1] + v->z * m->mat[0][2],
		.y = v->x * m->mat[1][0] + v->y * m->mat[1][1] + v->z * m->mat[1][2],
		.z = v->x * m->mat[2][0] + v->y * m->mat[2][1] + v->z * m->mat[2][2]};
	return (0);
}
