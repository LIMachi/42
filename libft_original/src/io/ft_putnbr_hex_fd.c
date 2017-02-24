/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 17:12:51 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/21 06:32:26 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static void	sf_putnbr_hex_fd(int n, int fd)
{
	if (n / 16)
		sf_putnbr_hex_fd(n / 16, fd);
	if (n % 16 < 10)
		ft_putchar_fd('0' + n % 16, fd);
	else
		ft_putchar_fd('A' - 10 + n % 16, fd);
}

void		ft_putnbr_hex_fd(int n, int fd)
{
	ft_putchar('0');
	ft_putchar('x');
	sf_putnbr_hex_fd(n, fd);
}
