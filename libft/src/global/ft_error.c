/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 20:14:49 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/19 01:06:27 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

long	ft_error(long error, char *string)
{
	static long	silent = 0;

	if (error == ERROR_SILENT_ON)
		silent = 1;
	if (error == ERROR_SILENT_OFF)
		silent = 0;
	if (error == ERROR_GET_SILENT)
		return (silent);
	if (silent == 0 || string != NULL)
		ft_putstr_fd("[ft_error] - ", 2);
	if (string != NULL)
		ft_putstr_fd(string, 2);
	if (error >= 0)
		(void)ft_global_error((error ? ERROR_SET : ERROR_ERRNO) |
								(silent ? 0 : ERROR_PRINT), 0);
	return (0);
}
