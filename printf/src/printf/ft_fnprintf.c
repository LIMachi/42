/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fnprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 20:39:35 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/28 01:55:29 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int	ft_fnprintf(FILE *stream, size_t size, const char *format, ...)
{
	int		out;
	va_list	ap;

	va_start(ap, format);
	out = ft_vfnprintf(stream, size, format, ap);
	va_end(ap);
	return (out);
}
