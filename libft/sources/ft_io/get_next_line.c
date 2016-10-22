/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 14:00:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/14 14:09:59 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			sf_read_until_char(int fd, char c, char **before,
					char **after)
{
	char	buff[BUFF_SIZE + 1];
	char	*t1;
	char	*t2;
	int		r;
	int		l;

	t1 = NULL;
	while ((r = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[r] = 0;
		if ((t2 = ft_strjoin(t1, buff)) == NULL)
			return (-1);
		if (t1 != NULL)
			free(t1);
		if ((t1 = t2) && ft_strchr(t1, c) != NULL && ft_strchr(t1, c) != t1)
		{
			*before = ft_strsub(t1, 0, ft_strchr(t1, c) - t1);
			if ((l = ft_strlen(t1) - (ft_strchr(t1, c) - t1 - 1)) > 0)
				*after = ft_strsub(t1, ft_strchr(t1, c) - t1 + 1, l);
			free(t1);
			return (1);
		}
	}
	*before = t1;
	return (r);
}

static int			sf_get_next_line(const int fd, char **line,
					t_gnl_tcf tcf[FD_LIMIT])
{
	char	*tmp_str;
	char	**tmp_ptr;
	int		r;

	if ((tmp_ptr = (char **)ft_memalloc(sizeof(char *))) == NULL)
		return (-1);
	if ((r = sf_read_until_char(fd, '\n', tmp_ptr, tcf[fd].ptr)) == -1)
	{
		free(tmp_ptr);
		return (-1);
	}
	r = r || (*tmp_ptr != NULL);
	tcf[fd].str = *tcf[fd].ptr;
	if (*line != NULL)
	{
		tmp_str = *line;
		*line = ft_strjoin(tmp_str, *tmp_ptr);
		free(tmp_str);
		free(tmp_ptr);
	}
	else
		*line = *tmp_ptr;
	r = r || ((*line != NULL) && (**line != 0));
	return (r);
}

int					get_next_line(const int fd, char **line)
{
	static t_gnl_tcf	tcf[FD_LIMIT] = {{.ptr = NULL, .str = NULL}};
	char				*tmp_str;

	if (fd < 0 || fd > FD_LIMIT || line == NULL
		|| BUFF_SIZE < 0 || BUFF_SIZE > SSIZE_MAX)
		return (-1);
	*line = NULL;
	if (tcf[fd].str != NULL && tcf[fd].ptr != NULL)
	{
		if ((tmp_str = ft_strchr(tcf[fd].str, '\n')) != NULL)
		{
			*line = ft_strsub(tcf[fd].str, 0, tmp_str - tcf[fd].str);
			tcf[fd].str = tmp_str + 1;
			return (1);
		}
		*line = ft_strdup(tcf[fd].str);
		ft_memdel((void **)tcf[fd].ptr);
	}
	else if ((tcf[fd].ptr = (char **)ft_memalloc(sizeof(char *))) == NULL)
		return (-1);
	return (sf_get_next_line(fd, line, tcf));
}
