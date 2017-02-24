/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 21:03:26 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/07 01:00:49 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#if 0

char	*ft_readfile(int fd)
{
	char	buff[BUFF_SIZE];
	int		r;
	int		size;
	char	*t_str;
	char	*file;

	size = 1;
	file = NULL;
	t_str = NULL;
	while ((r = read(fd, buff, BUFF_SIZE)))
	{
		if ((t_str = (char *)ft_malloc(sizeof(char) * (r + size))) == NULL)
			return (NULL);
		if (file != NULL)
		{
			ft_strcpy(t_str, file);
			ft_free(file);
		}
		ft_memcpy(t_str + size - 1, buff, r);
		file = t_str;
		size += r;
	}
	if (file != NULL && file[size - 1] != '\0')
		file[size - 1] = '\0';
	return (file);
}

#else

char	*ft_readfile(int fd)
{
	int		ret;
	char	*str;
	char	*str2;
	char	buf[4096 + 1];

	if (fd == -1)
		return (NULL);
	str = ft_strnew(0);
	while ((ret = read(fd, buf, 4096)))
	{
		buf[ret] = '\0';
		str2 = ft_strnew(ret);
		ft_strcpy(str2, buf);
		str = ft_strmerge(str, str2);
	}
	if (ret == -1)
	{
		ft_strdel(&str);
		return (NULL);
	}
	return (str);
}

#endif
