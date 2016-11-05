/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/15 00:21:53 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/03 19:47:18 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftx.h>

void	fdf(int ***map, t_point size)
{
	t_mlx_data	*data;

	if ((data = ftx_data(GDX_NEW)) == NULL)
		return ;
	init_mlx_data();
	main_window_init(map, size);
	mlx_loop_hook(data->mlx, ftx_update, (void*)data);
	mlx_loop(data->mlx);
}

int		main(int argc, char **argv)
{
	int		***map;
	t_point	size;
	int		fd;

	if (argc != 2)
	{
		write(1, "Usage: ", 7);
		write(1, argv[0], ft_strlen(argv[0]));
		write(1, " <filename>\n", 25);
		return (0);
	}
	ft_init();
	size = fdf_parse_file0(argv[1]);
	if (size.y == -1)
		return (0);
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return (0);
	if ((map = (int ***)ft_tab3dalloc(size.x + 1, size.y + 1, 2,
											sizeof(int))) == NULL)
		return (0);
	fdf_parse_file(map, fd, 0x00FFFF);
	close(fd);
	fdf(map, size);
	return (0);
}
