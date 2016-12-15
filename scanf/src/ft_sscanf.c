/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sscanf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 15:19:18 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/05 15:49:09 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libscanfft.h>

int	ft_sscanf(const char *str, const char *format, ...)
{
	va_list		ap;
	int			out;

	va_start(ap, format);
	out = ft_vsscanf(str, format, ap);
	va_end(ap);
	return (out);
}
