/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 14:12:23 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/18 13:18:57 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_tab_free(void **tab, int y)
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
				ft_free(tab[i]);
				tab[i] = NULL;
			}
	}
	else
		while (tab[++i])
		{
			ft_free(tab[i]);
			tab[i] = NULL;
		}
	ft_free(tab);
}
