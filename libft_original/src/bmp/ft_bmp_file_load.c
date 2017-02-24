/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bmp_file_load.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 19:34:13 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/18 23:30:16 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static void				*sf_bmp_file_load_error(t_ft_fd *fd, t_bitmap *out)
{
	if (out)
	{
		if (out->bmp)
			ft_free(out->bmp);
		ft_free(out);
	}
	ft_close(fd);
	return (NULL);
}

inline static t_bitmap	*sf_bitmap_file_load(t_bitmap *out, int i, t_ft_fd *fd,
										t_bitmap_file_header header)
{
	if ((out->bmp = (unsigned char*)ft_malloc(sizeof(unsigned char*) *
			out->info.size_image)) == NULL)
		return (sf_bmp_file_load_error(fd, out));
	i = header.offset - out->info.dib_size - sizeof(t_bitmap_file_header);
	if (ft_lseek(fd, i, SEEK_CUR) < i)
		return (sf_bmp_file_load_error(fd, out));
	if (ft_read(fd, out->bmp, out->info.size_image) <
		(int)out->info.size_image)
		return (sf_bmp_file_load_error(fd, out));
	ft_close(fd);
	return (out);
}

t_bitmap				*ft_bitmap_file_load(char *path)
{
	t_ft_fd					fd;
	t_bitmap_file_header	header;
	t_bitmap				*out;
	int						i;

	if (path == NULL || (fd = ft_open(path, O_RDONLY | O_BINARY, 0)).fd == -1)
		return (NULL);
	out = NULL;
	if (ft_read(&fd, &header, sizeof(t_bitmap_file_header))
		< (int)sizeof(t_bitmap_file_header) || header.file_type != 0x4D42
		|| (out = (t_bitmap*)ft_malloc(sizeof(t_bitmap))) == NULL)
		return (sf_bmp_file_load_error(&fd, out));
	out->info = (t_dib_header){.dib_size = 0};
	i = (int)sizeof(DWORD);
	if (ft_read(&fd, &(out->info.dib_size), i) < i
		|| !(i = out->info.dib_size - sizeof(DWORD))
		|| ft_read(&fd, &(out->info.width), i) < i)
		return (sf_bmp_file_load_error(&fd, out));
	return (sf_bitmap_file_load(out, i, &fd, header));
}
