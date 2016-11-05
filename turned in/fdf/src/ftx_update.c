/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 08:44:01 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/02 08:55:28 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftx.h>

#if NORM42 == 0

static int	ftx_update0(t_window *tmpwin, int f, struct timespec time)
{
	t_image	*tmpimg;

	tmpwin->last_frame = f;
	tmpwin->last_time = time;
	ftx_clear_img(tmpwin->vbuffer);
	if (tmpwin->up_func != NULL)
		tmpwin->up_func(tmpwin);
	tmpimg = tmpwin->images;
	while (tmpimg != NULL)
	{
		if (tmpimg->fill_func)
			tmpimg->fill_func(tmpwin, tmpimg);
		if (tmpimg->update && !(tmpimg->update = 0))
			ftx_put_img_to_img(tmpwin->vbuffer, tmpimg, 0);
		tmpimg = tmpimg->next;
	}
	mlx_put_image_to_window(((t_mlx_data*)ptr)->mlx, tmpwin->win,
		tmpwin->vbuffer->ptr, tmpwin->vbuffer->pos.x,
		tmpwin->vbuffer->pos.y);
}

int			ftx_update(void *ptr)
{
	t_window		*tmpwin;
	struct timespec	time;
	int				f;

	clock_gettime(CLOCK_REALTIME, &time);
	tmpwin = ((t_mlx_data*)ptr)->windows;
	while (tmpwin != NULL)
	{
		f = time.tv_nsec / (1 + 1000000000L / tmpwin->wfps);
		if ((f != tmpwin->last_frame ||
			time.tv_sec != tmpwin->last_time.tv_sec))
		{
			if (time.tv_sec != tmpwin->last_time.tv_sec)
			{
				tmpwin->fps = tmpwin->frames;
				tmpwin->frameloss += (tmpwin->frames < tmpwin->wfps);
				tmpwin->frames = 1;
			}
			else
				tmpwin->frames++;
			ftx_update0(tmpwin, f, time);
		}
		tmpwin = tmpwin->next;
	}
	return (0);
}

#else
# if OS == LINUX
#  pragma message "Warning: NORM42 will disable the fps stabilisation on Linux."
#  pragma message "Please disable NORM42 (= 0/undef) to allow fps stabilisation"
# endif

int			ftx_update(void *ptr)
{
	t_window		*tmpwin;
	t_image			*tmpimg;

	tmpwin = ((t_mlx_data*)ptr)->windows;
	while (tmpwin != NULL)
	{
		ftx_clear_img(tmpwin->vbuffer);
		if (tmpwin->up_func != NULL)
			tmpwin->up_func(tmpwin);
		tmpimg = tmpwin->images;
		while (tmpimg != NULL)
		{
			if (tmpimg->fill_func)
				tmpimg->fill_func(tmpwin, tmpimg);
			if (tmpimg->update && !(tmpimg->update = 0))
				ftx_put_img_to_img(tmpwin->vbuffer, tmpimg, 0);
			tmpimg = tmpimg->next;
		}
		mlx_put_image_to_window(((t_mlx_data*)ptr)->mlx, tmpwin->win,
			tmpwin->vbuffer->ptr, tmpwin->vbuffer->pos.x,
			tmpwin->vbuffer->pos.y);
		tmpwin = tmpwin->next;
	}
	return (0);
}

#endif
