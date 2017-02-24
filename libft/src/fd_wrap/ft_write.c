/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/23 00:32:17 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/02 14:47:35 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

ssize_t	ft_write(t_ft_fd *fd, const void *buf, size_t count)
{
	ssize_t	w;

	w = write(fd->fd, buf, count);
	if (w == -1)
		return (ft_error(0, "write call made by ft_write failled: ") - 1);
	fd->pos += w;
	return (w);
}
