/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dirname.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 06:59:50 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/25 07:54:06 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** Extract the path to the directory of the file/folder pointed by path
** Return the string  before the last / followed by a name
** If no path can be found, "." is returned
** The string returned is allocated and must be freed
*/

char	*ft_dirname(char *path)
{
	char	*last;
	char	*tmp;

	if (path == NULL || path[0] == '\0' ||
			(last = ft_strrchr(path, '/')) == NULL)
		return (ft_strdup("."));
	if (last != path && last[1] == '\0')
	{
		tmp = last;
		while (tmp != path && tmp[-1] == '/')
			--tmp;
		if (tmp != path)
			last = ft_memrchr(path, '/', (size_t)tmp - (size_t)path);
	}
	if (last != path)
	{
		tmp = last;
		while (tmp != path && tmp[-1] == '/')
			--tmp;
		if (tmp == path)
			return (ft_strdup("/"));
		else
			return (ft_strndup(path, (size_t)tmp - (size_t)path));
	}
	return (ft_strdup("/"));
}
