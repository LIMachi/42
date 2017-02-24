/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/19 00:32:45 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** copies at most n characters from src to dst
** if n is less than the length of src, no null character will be present at the
** end of dst
** if n is more than the length of src, the extra characters in dst after the
** null character copied from src will also be null characters
** if n is more than the length of dst or dst is NULL or src is NULL,
** then segfault might occur
** if n is zero, nothing will appen (and no segfault should occur because of a
** NULL dst or NULL src)
** return a pointer to dst
*/

#if !defined(NORM_LIBFT) || NORM_LIBFT == 1

/*
** norm libft, this function segfault on NULL pointers
*/

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t	i;

	i = (size_t)-1;
	while (++i < n && src[i] != '\0')
		dst[i] = src[i];
	while (i < n)
		dst[i++] = '\0';
	return (dst);
}

#else

/*
** Other norm: will return dst if src or dst is NULL or if n is 0
*/

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t	i;

	if (dst == NULL || src == NULL || n == 0)
		return (dst);
	i = (size_t)-1;
	while (++i < n && src[i] != '\0')
		dst[i] = src[i];
	while (i < n)
		dst[i++] = '\0';
	return (dst);
}

#endif
