/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vasnprintf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lee <lee@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 20:25:07 by lee               #+#    #+#             */
/*   Updated: 2017/02/26 04:21:45 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int	ft_vasnprintf(char **strn, size_t size, const char *format, va_list ap)
{
	va_list	tap;
	int		nsize;

	if (strn == NULL)
		return (-1);
	*strn = NULL;
	va_copy(tap, ap);
	if ((nsize = ft_vsnprintf(NULL, size, format, tap)) == -1)
		return (-1);
	va_end(tap);
	if ((*strn = ft_malloc(sizeof(char) * (nsize + 1))) == NULL)
		return (-1);
	return (ft_vsnprintf(*strn, size, format, ap));
}
