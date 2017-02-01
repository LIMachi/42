/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_name.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 17:41:22 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/18 23:51:31 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** Extract the name of the file/folder pointed by path
** Return the last string after a / (but will remove trailling /)
** The string returned is allocated and must be freed
*/

char	*ft_path_name(char *path)
{
	char	*tmp;

	tmp = ft_strrchr(path, '/');
	while ((tmp[1] == '\0' || tmp[1] == '/') && (size_t)tmp > (size_t)path)
	{
		--tmp;
		while ((size_t)tmp > (size_t)path && *tmp != '/')
			--tmp;
	}
	if (*tmp != '\0')
		++tmp;
	return (ft_strndup(tmp, ft_strcspn(tmp, "/")));
}
