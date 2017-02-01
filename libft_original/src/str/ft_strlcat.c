/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/19 00:23:13 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#if !defined(NORM_LIBFT) || NORM_LIBFT == 1

/*
** norm libft, this function segfault on NULL pointers
*/

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	dstlen;
	int		i;

	srclen = ft_strlen(src);
	dstlen = ft_strlen(dst);
	i = 0;
	while (i < (int)(dstsize - dstlen - 1) && src[i])
	{
		dst[i + dstlen] = src[i];
		++i;
	}
	dst[i + dstlen] = 0;
	if (dstsize <= dstlen)
		return (srclen + dstsize);
	return (srclen + dstlen);
}

#else

/*
** Other norm: will return 0 if dst is NULL and length of dst if src is NULL
*/

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	dstlen;
	int		i;

	if (dst == NULL)
		return (0);
	dstlen = ft_strlen(dst);
	if (src == NULL)
		return (dstlen);
	srclen = ft_strlen(src);
	i = 0;
	while (i < (int)(dstsize - dstlen - 1) && src[i])
	{
		dst[i + dstlen] = src[i];
		++i;
	}
	dst[i + dstlen] = 0;
	if (dstsize <= dstlen)
		return (srclen + dstsize);
	return (srclen + dstlen);
}

#endif
