/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puttab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 18:52:52 by hmartzol          #+#    #+#             */
/*   Updated: 2016/02/08 19:10:18 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_puttab(char **tab)
{
	int i;

	if (tab == NULL)
		return ;
	i = 0;
	while (tab[i] != NULL)
	{
		ft_putnbr(i);
		ft_putstr("\t: ");
		ft_putendl(tab[i]);
		++i;
	}
}
