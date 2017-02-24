/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vscanf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 15:35:12 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/05 15:41:36 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libscanfft.h>

int	ft_vscanf(const char *format, va_list ap)
{
	return (ft_vdscanf(STDIN_FILENO, format, ap));
}
