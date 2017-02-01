/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 0000/00/00 00:00:00 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/18 23:23:33 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_matrix	*ft_matrix_new(const int x, const int y)
{
	t_matrix	*out;

	if (x < 1 || y < 1)
		return (NULL);
	if ((out = (t_matrix*)ft_malloc(sizeof(t_matrix))) == NULL)
		return (NULL);
	if ((out->mat = (double**)ft_tab_alloc(x, y, sizeof(double))) == NULL)
	{
		ft_free(out);
		return (NULL);
	}
	out->size.x = x;
	out->size.y = y;
	return (out);
}
