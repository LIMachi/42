/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bmp_file_save.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 19:34:13 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/21 01:36:17 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** warning, might erase file with the same path has the one passed in 1st arg
** returns 0 on succes and -1 on error
*/

int			ft_bitmap_file_save(char *path, t_bitmap *bmp)
{
	t_ft_fd					fd;
	t_bitmap_file_header	header;

	if (path == NULL || bmp == NULL || bmp->bmp == NULL ||
		bmp->info.dib_size <= 0 || bmp->info.size_image <= 0 ||
		(fd = ft_open(path, O_WRONLY | O_BINARY | O_CREAT | O_TRUNC,
			S_IDEFAULT)).fd == -1)
		return (-1);
	header.file_type = 0x4D42;
	header.file_size = sizeof(t_bitmap_file_header) + bmp->info.dib_size +
													bmp->info.size_image;
	header.reserved = 0;
	header.offset = sizeof(t_bitmap_file_header) + bmp->info.dib_size;
	if (ft_write(&fd, &header, sizeof(header)) == -1 ||
		ft_write(&fd, &(bmp->info), bmp->info.dib_size) == -1 ||
		ft_write(&fd, bmp->bmp, bmp->info.size_image) == -1)
		return (-1);
	return (0);
}
