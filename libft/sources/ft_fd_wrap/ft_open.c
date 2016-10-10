/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 20:05:19 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/10 11:55:20 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** wrapper function to open, generate a special type of fd
*/

t_ft_fd	ft_open(const char *path, int flags)
{
	char	*tmp;
	int		fd;

	if (path == NULL)
	{
		ft_error(ERROR_SET, EINVAL);
		return ((t_ft_fd){-1, 0, NULL, 0});
	}
	if ((fd = open(path, flags)) < 0)
	{
		ft_error(ERROR_ERRNO, 0);
		return ((t_ft_fd){-1, 0, NULL, 0});
	}
	if ((tmp = ft_strdup(path)) == NULL)
		return ((t_ft_fd){-1, 0, NULL, 0});
	return ((t_ft_fd){fd, 0, tmp, flags});
}
