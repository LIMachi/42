/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 20:11:37 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/28 01:55:26 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int	ft_dprintf(int fd, const char *format, ...)
{
	int		out;
	va_list	ap;

	va_start(ap, format);
	out = ft_vdnprintf(fd, -1ul, format, ap);
	va_end(ap);
	return (out);
}
