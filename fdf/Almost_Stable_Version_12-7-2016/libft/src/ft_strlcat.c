/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/02/08 19:18:30 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

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
