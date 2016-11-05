/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/15 08:33:15 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/31 16:16:53 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftx.h>

t_image	*ftx_get_image(t_window *win, int id)
{
	t_image	*tmp;

	if (win == NULL)
		return (NULL);
	tmp = win->images;
	while (tmp != NULL && tmp->id != id)
		tmp = tmp->next;
	if (tmp && tmp->id == id)
		return (tmp);
	tmp = win->images->prev;
	while (tmp != NULL && tmp->id != id)
		tmp = tmp->prev;
	if (tmp && tmp->id == id)
		return (tmp);
	return (NULL);
}

t_image	*ftx_new_image(t_point size)
{
	t_image	*img;
	void	*mlx;
	int		error;

	if ((img = (t_image*)ft_memalloc(sizeof(t_image))) == NULL)
		return (NULL);
	img->size = size;
	error = 1;
	if (ftx_data(GDX_ACCES))
		if ((mlx = ftx_data(GDX_ACCES)->mlx))
			if ((img->ptr = mlx_new_image(mlx, size.x, size.y)))
				if ((img->data = (int *)mlx_get_data_addr(img->ptr,
		&(img->bpp), &(img->size_line), &(img->endian))))
					error = 0;
	if (error)
	{
		if (img->ptr)
			mlx_destroy_image(mlx, img->ptr);
		ft_memdel((void**)img);
	}
	return (img);
}

int		ftx_free_image(t_image *img)
{
	void	*mlx;

	if (!ftx_data(GDX_ACCES) || !(mlx = ftx_data(GDX_ACCES)->mlx))
		return (-1);
	if (img == NULL)
		return (1);
	if (img->ptr)
		mlx_destroy_image(mlx, img->ptr);
	if (img->next)
	{
		if (img->prev)
		{
			img->prev->next = img->next;
			img->next->prev = img->prev;
		}
		else
			img->next->prev = NULL;
	}
	else if (img->prev)
		img->prev->next = NULL;
	free(img);
	return (0);
}

int		ftx_free_all_images(t_image *img)
{
	void	*mlx;
	t_image	*tmp;

	if (!ftx_data(GDX_ACCES) || !(mlx = ftx_data(GDX_ACCES)->mlx))
		return (-1);
	if (img == NULL)
		return (1);
	while (img->next)
		img = img->next;
	tmp = img;
	while (tmp)
	{
		tmp = img->prev;
		if (img->ptr)
			mlx_destroy_image(mlx, img->ptr);
		free(img);
	}
	return (0);
}

void	ftx_add_image(t_window *win, t_image *img, int id)
{
	t_image		*tmp;

	img->id = id;
	if (win->images == NULL)
		win->images = img;
	else
	{
		tmp = win->images;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = img;
	}
}
