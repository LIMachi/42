/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_unit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 0000/00/00 00:00:00 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/18 23:24:38 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_matrix	*ft_matrix_unit(const int size)
{
	t_matrix	*out;
	t_point		pos;

	if (size < 1 || (out = (t_matrix*)ft_malloc(sizeof(t_matrix))) == NULL)
		return (NULL);
	if ((out->mat = (double**)ft_tab_alloc(size, size, sizeof(double))) == NULL)
		return (ft_free(out));
	out->size.x = size;
	out->size.y = size;
	pos.y = -1;
	while (++pos.y < size && (pos.x = -1))
		while (++pos.x < size)
			out->mat[pos.y][pos.x] = pos.x == pos.y;
	return (out);
}
