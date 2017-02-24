/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/18 23:59:49 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#if !defined(NORM_LIBFT) || NORM_LIBFT == 1

/*
** norm libft, this function segfault on NULL pointers
*/

char	*ft_strcpy(char *dst, const char *src)
{
	int i;

	i = -1;
	while (src[++i])
		dst[i] = src[i];
	dst[i] = '\0';
	return (dst);
}

#else

/*
** Other norm: will return dst if src is NULL, and will return NULL if dst is
** NULL
** Protected against segfault, non standard
*/

char	*ft_strcpy(char *dst, const char *src)
{
	int i;

	if (src == NULL)
		return (dst);
	if (dst == NULL)
		return (NULL);
	i = -1;
	while (src[++i])
		dst[i] = src[i];
	dst[i] = '\0';
	return (dst);
}

#endif
