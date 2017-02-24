/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_multply_vector.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/31 13:08:47 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_vector		ft_matrix_multply_vector(const t_vector v, const t_matrix *m)
{
	if (m == NULL)
		return (v);
	if (m->size.x != 3 || m->size.y != 3)
		return (v);
	return ((t_vector){
		.x = v.x * m->mat[0][0] + v.y * m->mat[0][1] + v.z * m->mat[0][2],
		.y = v.x * m->mat[1][0] + v.y * m->mat[1][1] + v.z * m->mat[1][2],
		.z = v.x * m->mat[2][0] + v.y * m->mat[2][1] + v.z * m->mat[2][2]});
}
