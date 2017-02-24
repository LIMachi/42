/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_block_alloc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 14:12:03 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/27 14:48:52 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** Create a table with a single block of memory.
** Such table must be freed by calling free only on the first pointer and none
** other, because all other pointers in the table (range tab[0] to tab[y]) are
** self references to said table.
** The main drawback is the danger of data corruption on overflow, but the
** benefit is an easy free call and bitmap style of data storage at tab[0]
** Note: the memory is not padded, acces might be slightly slower than standard
** tables.
*/

void	**ft_tab_block_alloc(size_t x, size_t y, size_t block)
{
	void	**out;
	size_t	i;
	size_t	ty;
	size_t	tx;

	if (x == 0 || y == 0 || block == 0)
		return (NULL);
	ty = y * sizeof(void *);
	tx = x * block;
	if ((out = ft_memalloc(ty + y * tx)) == NULL)
		return (out);
	i = (size_t)-1;
	while (++i < y)
		out[i] = (void *)&((char*)out)[i * tx + ty];
	return (out);
}
