/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 08:02:44 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/25 10:23:23 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** fake realpath, only resolve . and .. and remove ecces /
** if path dosen't start with / it will use ENV to get the local path
** if ENV is not set, return NULL and resolved_path is untouched
** if resolved_path is NULL, then it will malloc the returned string
*/

/*
** remove . and .. (replace them and the eventual preceding dir of .. with /)
*/

inline static void	sf_to_the_point(char resolved_path[PATH_MAX])
{
	size_t	st;
	char	*tmp;

	st = -1;
	while (resolved_path[++st] != '\0')
		if (st && resolved_path[st - 1] == '/' && resolved_path[st] == '.')
		{
			if (resolved_path[st + 1] == '.' &&
				(resolved_path[st + 2] == '/' || resolved_path[st + 2] == '\0'))
			{
				resolved_path[st] = '/';
				resolved_path[st + 1] = '/';
				tmp = &resolved_path[st - 1];
				while (tmp != resolved_path && *(--tmp) == '/')
					;
				if ((tmp = ft_memrchr(resolved_path, '/',
						(size_t)tmp - (size_t)resolved_path)) == NULL)
					tmp = resolved_path;
				ft_memset(tmp, '/', resolved_path - tmp + st + 1);
			}
			else if (resolved_path[st + 1] == '/' ||
					resolved_path[st + 1] == '\0')
				resolved_path[st] = '/';
		}
}

char				*ft_realpath(char *path, char resolved_path[PATH_MAX])
{
	char	*pwd;
	size_t	st;

	if (resolved_path == NULL)
		if ((resolved_path = ft_memalloc(sizeof(char) * PATH_MAX)) == NULL)
			return ((char*)ft_error(ENOMEM, "realpath failed memalloc\n"));
	if (path == NULL)
		path = ".";
	if (path[0] == '/')
		ft_memmove(resolved_path, path, ft_strlen(path));
	else
	{
		if ((pwd = ft_pwd()) == NULL)
			return ((char*)ft_error(ENOENV, "realpath failed pwd\n"));
		ft_memmove(resolved_path, pwd, st = ft_strlen(pwd));
		resolved_path[st] = '/';
		ft_memmove(resolved_path + st + 1, path, ft_strlen(path) + 1);
	}
	sf_to_the_point(resolved_path);
	(void)ft_path_clean_slashes(resolved_path);
	return (resolved_path);
}
