/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_substract.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 0000/00/00 00:00:00 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/09 08:20:51 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_matrix	*ft_matrix_substract(const t_matrix *a, const t_matrix *b)
{
	t_matrix	*out;
	t_point		pos;

	if (a == NULL || b == NULL || !ft_point_equal(a->size, b->size) ||
					(out = ft_matrix_new(a->size.x, a->size.y)) == NULL)
		return (NULL);
	pos.y = -1;
	while (++pos.y < a->size.y && (pos.x = -1))
		while (++pos.x < a->size.x)
			out->mat[pos.y][pos.x] = a->mat[pos.y][pos.x] -
									b->mat[pos.y][pos.x];
	return (out);
}
