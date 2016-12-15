/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scanf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 15:45:45 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/05 15:45:55 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libscanfft.h>

int	ft_scanf(const char *format, ...)
{
	va_list		ap;
	int			out;

	va_start(ap, format);
	out = ft_vscanf(format, ap);
	va_end(ap);
	return (out);
}
