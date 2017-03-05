/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_asnprintf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 20:24:08 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/28 01:55:13 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int	ft_asnprintf(char **strn, size_t size, const char *format, ...)
{
	int		out;
	va_list	ap;

	va_start(ap, format);
	out = ft_vasnprintf(strn, size, format, ap);
	va_end(ap);
	return (out);
}
