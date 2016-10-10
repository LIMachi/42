/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 20:11:20 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/10 11:55:24 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** wrapper function to read, uses t_ft_fd
*/

ssize_t	ft_read(t_ft_fd *fd, void *buf, size_t count)
{
	ssize_t	r;

	r = read(fd->fd, buf, count);
	if (r < 0)
		ft_error(ERROR_ERRNO, 0);
	fd->pos += r;
	return (r);
}
