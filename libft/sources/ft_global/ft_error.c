/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 20:14:49 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/14 14:44:59 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

long	ft_error(long error, char *string)
{
	if (string != NULL)
		ft_putstr_fd(string, 2);
	if (error)
		(void)ft_global_error(ERROR_SET | ERROR_PRINT, error);
	else
		(void)ft_global_error(ERROR_ERRNO, 0);
	return (0);
}
