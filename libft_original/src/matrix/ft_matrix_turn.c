/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_turn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 0000/00/00 00:00:00 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/09 09:05:22 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_matrix	*ft_matrix_turn(const t_matrix *matrix)
{
	t_matrix	*out;
	t_point		pos;

	if (matrix == NULL || (out =
		ft_matrix_new(matrix->size.y, matrix->size.x)) == NULL)
		return (NULL);
	pos.y = -1;
	while (++pos.y < matrix->size.y && (pos.x = -1))
		while (++pos.x < matrix->size.x)
			out->mat[pos.x][pos.y] = matrix->mat[pos.y][pos.x];
	return (out);
}
