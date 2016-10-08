/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lseek.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 23:15:40 by hmartzol          #+#    #+#             */
/*   Updated: 2016/08/23 00:44:25 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	sf_lseek(t_ft_fd *fd, off_t offset, char readbuff[BUFF_SIZE])
{
	int	r;
	int t;
	char zero;

	r = 1;
	t = 0;
	zero = 0;
	while (fd->pos < offset)
	{
		if (r)
			r = ft_read(fd, readbuff, offset > BUFF_SIZE ? BUFF_SIZE : offset);
		else
		{
			if ((fd->flags | O_WRONLY) || (fd->flags | O_RDWR))
				r = ft_write(fd, &zero, 1);
			else
				break ;
			if (r == 0)
				break ;
		}
		if (r == -1)
			return (ft_error(FT_ERROR_ERRNO, 0) * 0 - 1);
		t += r;
	}
	return (t);
}

#ifdef USE_LSEEK
off_t			ft_lseek(t_ft_fd *fd, off_t offset, int whence)
{
	off_t	off;

	off = lseek(fd->fd, offset, whence);
	if (off < 0)
		ft_error(FT_ERROR_ERRNO, 0);
	fd->pos = off;
	return (off);
}
#else
off_t			ft_lseek(t_ft_fd *fd, off_t offset, int whence)
{
	char	readbuff[BUFF_SIZE];
	off_t	out;

	if (whence == SEEK_CUR)
		offset += fd->pos;
	if (whence == SEEK_END)
		while ((out = ft_read(fd, readbuff, offset > BUFF_SIZE ? BUFF_SIZE :
																	offset)))
			if (out == -1)
				return (ft_error(FT_ERROR_ERRNO, 0) * 0 - 1);
	if (whence == SEEK_SET || whence == SEEK_CUR || whence == SEEK_END)
	{
		if (offset < fd->pos)
		{
			(void)ft_reopen(fd);
		}
		out = sf_lseek(fd, offset, readbuff);
	}
	else
		return (ft_error(FT_ERROR_SET, EINVAL) * 0 - 1);
	return (out);
}
#endif
