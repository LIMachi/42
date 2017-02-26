/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lee <lee@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 20:18:18 by lee               #+#    #+#             */
/*   Updated: 2017/02/25 20:18:42 by lee              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int	ft_sprintf(char *str, const char *format, ...)
{
	int		out;
	va_list	ap;

	va_start(ap, format);
	out = ft_vsnprintf(str, -1ul, format, ap);
	va_end(ap);
	return (out);
}
