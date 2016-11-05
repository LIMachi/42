/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_multiply.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 0000/00/00 00:00:00 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/09 08:13:44 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_matrix	*ft_matrix_multply(const t_matrix *a, const t_matrix *b)
{
	t_matrix	*out;
	t_point		pos;
	int			i;

	if (a == NULL || b == NULL || a->size.x != b->size.y ||
						(out = ft_matrix_new(b->size.x, a->size.y)) == NULL)
		return (NULL);
	pos.y = -1;
	while (++pos.y < out->size.y && (pos.x = -1))
		while (++pos.x < out->size.x && (i = -1))
		{
			out->mat[pos.y][pos.x] = 0;
			while (++i < a->size.x)
				out->mat[pos.y][pos.x] += a->mat[pos.y][i] * b->mat[i][pos.x];
		}
	return (out);
}
