/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reopen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 23:52:19 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/21 01:44:58 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** reopen a file with the same path but might change the flags (like O_CREAT)
** note: the same pointer to path will be used, no memory will be freed or
** allocated, unless an error apen in the opening, then path will be freed
*/

t_ft_fd	ft_reopen(t_ft_fd *fd)
{
	if (!fd || fd->path == NULL)
	{
		ft_error(EBADF, "ft_reopen call failled: ");
		return ((t_ft_fd){-1, 0, NULL, 0, 0});
	}
	if (close(fd->fd) == -1)
	{
		ft_error(0, "close call made by ft_reopen failled: ");
		return ((t_ft_fd){-1, 0, NULL, 0, 0});
	}
	if (fd->flags | O_CREAT)
		fd->flags ^= O_CREAT;
	if ((fd->fd = open(fd->path, fd->flags, fd->rights)) < 0)
	{
		ft_error(0, "open call made by reopen failled: ");
		ft_free(fd->path);
		return ((t_ft_fd){-1, 0, NULL, 0, 0});
	}
	return (*fd);
}
