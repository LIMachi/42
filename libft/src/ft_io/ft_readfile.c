/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 21:03:26 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/18 13:43:38 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_readfile(int fd)
{
	char	buff[BUFF_SIZE];
	int		r;
	int		size;
	char	*t_str;
	char	*file;

	size = 1;
	file = NULL;
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
	if (file[size - 1])
		file[size - 1] = 0;
	return (file);
}
