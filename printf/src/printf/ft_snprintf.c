/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 20:15:46 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/28 01:55:39 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int	ft_snprintf(char *str, size_t size, const char *format, ...)
{
	int		out;
	va_list	ap;

	va_start(ap, format);
	out = ft_vsnprintf(str, size, format, ap);
	va_end(ap);
	return (out);
}
