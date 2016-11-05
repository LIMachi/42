/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 23:29:02 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/14 14:34:35 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_close(t_ft_fd *fd)
{
	if (!fd || fd->path == NULL)
		return (ft_error(EBADF, "ft_close call failled: ") - 1);
	ft_free(fd->path);
	if (close(fd->fd) == -1)
		return (ft_error(0, "close call made by ft_close failled: ") - 1);
	return (0);
}
