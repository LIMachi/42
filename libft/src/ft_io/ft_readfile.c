/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 21:03:26 by hmartzol          #+#    #+#             */
/*   Updated: 2016/02/08 21:16:35 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#define READBUFF 80

char	*ft_readfile(int fd)
{
	char	buff[READBUFF];
	int		r;
	int		size;
	char	*t_str;
	char	*file;

	size = 1;
	file = NULL;
	while ((r = read(fd, buff, READBUFF)))
	{
		if ((t_str = (char *)malloc(sizeof(char) * (r + size))) == NULL)
			return (NULL);
		if (file != NULL)
		{
			ft_strcpy(t_str, file);
			free(file);
		}
		ft_memcpy(t_str + size - 1, buff, r);
		file = t_str;
		size += r;
	}
	if (file[size - 1])
		file[size - 1] = 0;
	return (file);
}
