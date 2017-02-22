/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_bin_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 05:02:22 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/21 15:14:27 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_putnbr_bin_fd(unsigned long nbr, int fd)
{
	unsigned long	i;

	i = 1ul << ((sizeof(unsigned long) << 3ul) - 1);
	ft_putstr_fd("0b", fd);
	while (i)
	{
		ft_putchar_fd(nbr & i ? '1' : '0', fd);
		i >>= 1ul;
	}
}
