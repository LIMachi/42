/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_alloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 14:12:03 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/18 13:19:01 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	**ft_tab_alloc(int x, int y, size_t block)
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
				ft_free(out[i]);
			ft_free(out);
			return (NULL);
		}
	return (out);
}
