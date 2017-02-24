/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab3d_alloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 14:12:12 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/18 13:18:59 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** the order of 3d tab is [y][x][z]
*/

void	***ft_tab3d_alloc(int x, int y, int z, size_t block)
{
	void	***out;
	int		i;
	int		j;

	if ((out = (void ***)ft_tab_alloc(x, y, sizeof(void *))) == NULL)
		return (NULL);
	i = -1;
	while (++i < y && (j = -1))
		while (++j < x)
			if ((out[i][j] = ft_memalloc(block * z)) == NULL)
			{
				while (--i >= -1)
				{
					while (--j >= -1)
						ft_free(out[i][j]);
					j = x;
				}
				ft_tab_free((void **)out, y);
				return (NULL);
			}
	return (out);
}
