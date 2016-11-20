/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_screenshoot.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 16:15:01 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/18 16:37:06 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftx.h>

int	ftx_screenshoot(t_window *win, const char *folder_path)
{
	t_ubmp		ubmp;
	t_bitmap	*bmp;
	char		buff[1 MEM_K];
	size_t		len;

	if (win == NULL)
		return (-1);
	if (folder_path == NULL)
		folder_path = "./";
	ubmp.size = win->vbuffer->size;
	ubmp.data = win->vbuffer->data;
	if ((bmp = ft_ubmp_to_bmp(&ubmp)) == NULL)
		return (-1);
	ft_memmove(buff, folder_path, len = ft_strlen(folder_path));
	ft_memmove(&buff[len], win->name, ft_strlen(win->name));
	ft_memmove(&buff[len + ft_strlen(win->name)], ".bmp", 5);
	ft_bitmap_file_save(buff, bmp);
	ft_free(bmp->bmp);
	ft_free(bmp);
	return (0);
}