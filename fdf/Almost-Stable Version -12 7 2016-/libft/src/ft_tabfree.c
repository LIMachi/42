/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/00/00 00:00:00 by hmartzol          #+#    #+#             */
/*   Updated: 2016/00/00 00:00:00 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_tabfree(void **tab, int y)
{
	int	i;

	if (tab == NULL)
		return ;
	i = -1;
	if (y >= 0)
	{
		while (++i < y)
			if (tab[i])
			{
				free(tab[i]);
				tab[i] = NULL;
			}
	}
	else
		while (tab[++i])
		{
			free(tab[i]);
			tab[i] = NULL;
		}
	free(tab);
}
