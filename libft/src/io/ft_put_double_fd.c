/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_double_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 04:46:51 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/21 15:13:34 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_put_double_fd(double v, int precision, int fd)
{
	ft_putnbr_fd((int)v, fd);
	v = ABS(v);
	ft_putchar_fd('.', fd);
	while (precision-- > 0)
		ft_putchar_fd("0123456789"[((long long)(v *= 10.0)) % 10ll], fd);
}
