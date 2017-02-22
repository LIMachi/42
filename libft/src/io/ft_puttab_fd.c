/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puttab_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 18:52:52 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/14 14:09:53 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_puttab_fd(char **tab, int fd)
{
	int i;

	if (tab == NULL)
		return ;
	i = 0;
	while (tab[i] != NULL)
	{
		ft_putnbr_fd(i, fd);
		ft_putstr_fd("\t: ", fd);
		ft_putendl_fd(tab[i], fd);
		++i;
	}
}
