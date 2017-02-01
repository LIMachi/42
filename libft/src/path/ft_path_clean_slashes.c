/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_clean_slashes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 09:15:45 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/25 10:08:08 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** remove ecces slashes in path by reordering characters in path and adding
** an eventual '\0' terminator
** use path itself, the pointer returned should be the same as the one in param
** passing a non array nor allocated string will result in a bus error
** (ft_path_clean_slashes("//thing//") will bus error)
** (char *p = "//test//"; ft_path_clean_slashes(p); will bus error)
** (char p[] = "//test//"; ft_path_clean_slashes(p); will be fine)
** (ft_path_clean_slashes(ft_strdup("//thing//"));
** 	will be fine, but must be freed)
*/

char	*ft_path_clean_slashes(char *path)
{
	int	pad;
	int	i;

	if (path == NULL)
		return (NULL);
	pad = 0;
	i = -1;
	while (path[++i] != '\0')
	{
		if (pad)
			path[i - pad] = path[i];
		if (path[i] == '/')
			while (path[i + 1] == '/')
			{
				++pad;
				++i;
			}
	}
	path[i - pad] = '\0';
	return (path);
}
