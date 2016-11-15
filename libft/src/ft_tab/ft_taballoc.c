/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_taballoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 14:12:03 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/14 14:12:06 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	**ft_taballoc(int x, int y, size_t block)
{
	void	**out;
	int		i;

	if ((out = (void **)ft_memalloc(sizeof(void *) * y)) == NULL)
		return (NULL);
	i = -1;
	while (++i < y)
		if ((out[i] = ft_memalloc(block * x)) == NULL)
		{
			while (--i >= 0)
				free(out[i]);
			free(out);
			return (NULL);
		}
	return (out);
}
