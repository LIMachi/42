/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parse_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 16:27:24 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/03 19:48:14 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftx.h>

t_point	fdf_parse_file0(char *filename)
{
	int		fd;
	char	*line;
	t_point	t;

	if ((fd = open(filename, O_RDONLY)) < 0)
		return ((t_point){.x = -1, .y = -1});
	t = ft_point(-1, -1);
	while (!(line = NULL) && get_next_line(fd, &line) == 1 && !(0 * ++t.y))
	{
		if (line[0] == '\0')
		{
			ft_free(line);
			continue ;
		}
		if (t.x == -1)
			t.x = ft_strcntw(line);
		else if (t.x != ft_strcntw(line))
			return ((t_point){.x = -1, .y = -1});
		ft_free(line);
	}
	if (t.y == -1)
		return (ft_point(-1, -1));
	close(fd);
	return (t);
}

void	fdf_parse_file(int ***map, int fd, int default_color)
{
	char	*line;
	char	*tmp;
	t_point	i;

	i.y = -1;
	while (!(line = NULL) && get_next_line(fd, &line) == 1 && !(0 * ++i.y))
		if (line[0] != '\0' || ft_free(line))
		{
			tmp = line;
			i.x = 0;
			map[i.y][i.x][0] = ft_atoi(tmp);
			map[i.y][i.x][1] = (ft_strchr(tmp, ',') != NULL &&
					ft_strchr(tmp, ',') < ft_strnw(tmp)) ?
					ft_atoi_extended(ft_strchr(tmp, ',') + 1) : default_color;
			while ((tmp = ft_strnw(tmp))[0] != 0 && !(0 * ++i.x))
			{
				map[i.y][i.x][0] = ft_atoi_extended(tmp);
				map[i.y][i.x][1] = (ft_strchr(tmp, ',') != NULL &&
					ft_strchr(tmp, ',') < ft_strnw(tmp)) ?
					ft_atoi_extended(ft_strchr(tmp, ',') + 1) : default_color;
			}
			ft_free(line);
		}
}
