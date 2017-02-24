/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/18 23:58:22 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#if !defined(NORM_LIBFT) || NORM_LIBFT == 1

/*
** norm libft, this function segfault on NULL pointers
*/

char	*ft_strcat(char *dst, const char *src)
{
	int i;
	int j;

	i = 0;
	while (dst[i])
		++i;
	j = -1;
	while (src[++j])
		dst[i + j] = src[j];
	dst[i + j] = 0;
	return (dst);
}

#else

/*
** Other norm: will return dst if src is NULL, and will return NULL if dst is
** NULL
** Protected against segfault, non standard
*/

char	*ft_strcat(char *dst, const char *src)
{
	int i;
	int j;

	if (src == NULL)
		return (dst);
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (dst[i])
		++i;
	j = -1;
	while (src[++j])
		dst[i + j] = src[j];
	dst[i + j] = 0;
	return (dst);
}

#endif
