/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 20:05:19 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/21 01:44:05 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** wrapper function to open, generate a special type of fd
*/

t_ft_fd	ft_open(const char *path, int flags, int rights)
{
	char	*tmp;
	int		fd;

	if (path == NULL)
	{
		ft_error(EINVAL, "ft_open call failled: ");
		return ((t_ft_fd){-1, 0, NULL, 0, 0});
	}
	if ((fd = open(path, flags, rights)) < 0)
	{
		ft_error(0, "open call made by ft_open failled: ");
		return ((t_ft_fd){-1, 0, NULL, 0, 0});
	}
	if ((tmp = ft_strdup(path)) == NULL)
		return ((t_ft_fd){-1, 0, NULL, 0, 0});
	return ((t_ft_fd){fd, 0, tmp, flags, rights});
}
