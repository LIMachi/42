/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/19 00:27:36 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** append up to n bytes of src to dst, null terminating the result
*/

#if !defined(NORM_LIBFT) || NORM_LIBFT == 1

/*
** norm libft, this function segfault on NULL pointers
*/

char	*ft_strncat(char *dst, const char *src, size_t n)
{
	int i;
	int j;

	i = 0;
	while (dst[i])
		++i;
	j = -1;
	while (src[++j] && n--)
		dst[i + j] = src[j];
	dst[i + j] = 0;
	return (dst);
}

#else

/*
** Other norm: return NULL if dst is NULL, return dst if src is NULL
*/

char	*ft_strncat(char *dst, const char *src, size_t n)
{
	int i;
	int j;

	if (dst == NULL)
		return (NULL);
	if (src == NULL)
		return (dst);
	i = 0;
	while (dst[i])
		++i;
	j = -1;
	while (src[++j] && n--)
		dst[i + j] = src[j];
	dst[i + j] = 0;
	return (dst);
}

#endif
