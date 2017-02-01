/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 14:00:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/18 23:44:12 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

inline static int	sf_ruco(const int fd, int c, char **container)
{
	char	buffer[BUFF_SIZE];
	int		r;
	char	*tmp;

	if (container == NULL || *container != NULL)
		return (-1 | ft_error(EINVAL, "invalid container passed to sf_ruco "));
	while ((r = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[r] = '\0';
		tmp = ft_stracat(*container, buffer);
		if (*container != NULL)
			ft_free(*container);
		*container = tmp;
		if (ft_strchr(buffer, c))
			break ;
	}
	if (r == -1)
		return (-1 | ft_error(0, "sf_ruco's call to read failed: "));
	if (r == 0 && *container == NULL)
		return (0);
	return (1);
}

inline static int	sf_gnl_0(const int fd, char *tab[FD_LIMIT])
{
	int		r;
	char	*ptr0;
	char	*ptr1;

	if (tab[fd] == NULL || ft_strchr(tab[fd], '\n') == NULL)
	{
		ptr0 = NULL;
		if ((r = sf_ruco(fd, '\n', &ptr0)) == -1)
			return (-1);
		if (r == 0 && tab[fd] == NULL)
			return (0);
		if ((ptr1 = ft_stracat(tab[fd], ptr0)) == NULL)
			return (-1);
		if (r == 1)
			ft_free(ptr0);
		if (tab[fd] != NULL)
			ft_free(tab[fd]);
		tab[fd] = ptr1;
	}
	return (1);
}

inline static int	sf_gnl_1(const int fd, char **line, char *tab[FD_LIMIT])
{
	char	*ptr0;
	char	*ptr1;

	if ((ptr0 = ft_strchr(tab[fd], '\n')) == NULL)
	{
		if ((*line = ft_strndup(tab[fd], ft_strlen(tab[fd]))) == NULL)
			return (-1);
		ft_free(tab[fd]);
		tab[fd] = NULL;
		return (1);
	}
	if ((*line = ft_strpdup(tab[fd], ptr0++)) == NULL)
		return (-1);
	if ((ptr1 = ft_strpdup(ptr0, ft_strchr(ptr0, '\0'))) == NULL)
		return (-1);
	ft_free(tab[fd]);
	tab[fd] = ptr1;
	return (1);
}

int					get_next_line(const int fd, char **line)
{
	static char		*tab[FD_LIMIT] = {0};
	int				r;

	if (fd < 0)
		return (-1 | ft_error(ENOENT, "incorect fd passed to get_next_line "));
	if (fd >= FD_LIMIT)
		return (-1 | ft_error(EBADF, "incorect fd passed to get_next_line "));
	if (line == NULL)
		return (-1 | ft_error(EINVAL, "**line in get_next_line is NULL "));
	if (*line != NULL)
		return (-1 | ft_error(EINVAL, "*line in get_next_line is not NULL "));
	if (BUFF_SIZE > READ_MAX)
		return (-1 | ft_error(ENOMEM, "BUFF_SIZE in get_next_line too big "));
	if ((r = sf_gnl_0(fd, tab)) != 1)
		return (r);
	return (sf_gnl_1(fd, line, tab));
}
