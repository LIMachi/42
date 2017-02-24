/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/19 00:14:49 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#if !defined(NORM_LIBFT) || NORM_LIBFT == 1

/*
** norm libft, this function segfault on NULL pointers
*/

char	*ft_strdup(const char *str)
{
	char	*out;
	int		len;

	len = ft_strlen(str) + 1;
	if ((out = (char*)ft_malloc(sizeof(char) * len)) == NULL)
		return (NULL);
	return ((char *)ft_memcpy(out, (void *)str, len));
}

#else

/*
** Other norm: will return NULL if str is NULL
*/

char	*ft_strdup(const char *str)
{
	char	*out;
	int		len;

	if (str == NULL)
		return (NULL);
	len = ft_strlen(str) + 1;
	if ((out = (char*)ft_malloc(sizeof(char) * len)) == NULL)
		return (NULL);
	return ((char *)ft_memcpy(out, (void *)str, len));
}

#endif
