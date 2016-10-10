/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 23:29:02 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/10 11:55:46 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_close(t_ft_fd *fd)
{
	if (!fd || fd->path == NULL)
	{
		ft_error(ERROR_SET, EBADF);
		return (-1);
	}
	free(fd->path);
	if (close(fd->fd) == -1)
	{
		ft_error(ERROR_ERRNO, 0);
		return (-1);
	}
	return (0);
}
