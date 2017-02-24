/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dscanf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 15:46:40 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/05 15:47:02 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libscanfft.h>

int	ft_dscanf(const int fd, const char *format, ...)
{
	va_list		ap;
	int			out;

	va_start(ap, format);
	out = ft_vdscanf(fd, format, ap);
	va_end(ap);
	return (out);
}
