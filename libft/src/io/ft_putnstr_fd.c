/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 15:03:54 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/07 00:59:42 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_putnstr_fd(char *str, int n, int fd)
{
	int	t;

	if (str == NULL || n <= 0)
		return (-1);
	t = ft_strlen(str);
	n = n < t ? n : t;
	ft_void(write(fd, str, n));
	if ((*ft_global_flags() & GF_FORCE_LOG) == GF_FORCE_LOG)
	{
		t = str[n];
		str[n] = '\0';
		ft_global_log(LOG_SET | LOG_STORE, str);
		str[n] = t;
	}
	return (n);
}
