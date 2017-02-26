/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vasprintf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lee <lee@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 20:26:04 by lee               #+#    #+#             */
/*   Updated: 2017/02/25 20:27:28 by lee              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int	ft_vasprintf(char **strn, const char *format, va_list ap)
{
	return (ft_vasnprintf(strn, -1ul, format, ap));
}
