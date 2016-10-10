/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reopen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 23:52:19 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/10 11:55:36 by hmartzol         ###   ########.fr       */
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
		ft_error(ERROR_SET, EBADF);
		return ((t_ft_fd){-1, 0, NULL, 0});
	}
	if (close(fd->fd) == -1)
	{
		ft_error(ERROR_ERRNO, 0);
		return ((t_ft_fd){-1, 0, NULL, 0});
	}
	if (fd->flags | O_CREAT)
		fd->flags ^= O_CREAT;
	if ((fd->fd = open(fd->path, fd->flags)) < 0)
	{
		free(fd->path);
		ft_error(ERROR_ERRNO, 0);
		return ((t_ft_fd){-1, 0, NULL, 0});
	}
	return (*fd);
}
