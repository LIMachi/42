/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab3dalloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 14:12:12 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/14 14:12:14 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	***ft_tab3dalloc(int x, int y, int z, size_t block)
{
	void	***out;
	int		i;
	int		j;

	if ((out = (void ***)ft_taballoc(x, y, sizeof(void *))) == NULL)
		return (NULL);
	i = -1;
	while (++i < y && (j = -1))
		while (++j < x)
			if ((out[i][j] = ft_memalloc(block * z)) == NULL)
			{
				while (--i >= -1)
				{
					while (--j >= -1)
						free(out[i][j]);
					j = x;
				}
				ft_tabfree((void **)out, y);
				return (NULL);
			}
	return (out);
}
