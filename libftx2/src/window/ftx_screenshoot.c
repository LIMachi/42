/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_screenshoot.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 16:15:01 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/21 17:15:05 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <libftx.h>

int	ftx_screenshoot(t_window *win, const char *folder_path)
{
	t_ubmp		ubmp;
	t_bitmap	*bmp;
	char		buff[BUFF_SIZE];
	size_t		len;

	if (win == NULL)
		return (-1);
	if (folder_path == NULL)
		folder_path = "./";
	ubmp.size = win->vbuffer->size;
	ubmp.data = (int*)ft_memdup(win->vbuffer->data,
								4 * ubmp.size.x * ubmp.size.y);
	len = 0;
	while (len < (size_t)(ubmp.size.x * ubmp.size.y))
		ubmp.data[len++] |= 0xFF000000;
	if ((bmp = ft_ubmp_to_bmp(&ubmp)) == NULL)
		return (-1);
	ft_memmove(buff, folder_path, len = ft_strlen(folder_path));
	ft_memmove(&buff[len], win->name, ft_strlen(win->name));
	ft_memmove(&buff[len + ft_strlen(win->name)], ".bmp", 5);
	ft_bitmap_file_save(buff, bmp);
	ft_free(ubmp.data);
	ft_free(bmp->bmp);
	ft_free(bmp);
	return (0);
}
