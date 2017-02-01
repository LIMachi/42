/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/19 00:03:25 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#if !defined(NORM_LIBFT) || NORM_LIBFT == 1

/*
** norm libft, this function segfault on NULL pointers and have bad result on
** c being truncated by a char cast
*/

char	*ft_strchr(char *s, int c)
{
	char	*ptr;

	ptr = s;
	while (*ptr && *ptr != (char)c)
		++ptr;
	if (*ptr != (char)c)
		return (NULL);
	return (ptr);
}

#else

/*
** Other norm: will return NULL if s is NULL, or if c is not a char
** Protected against segfault, non standard
*/

char	*ft_strchr(char *s, int c)
{
	char	*ptr;

	if (s == NULL || c > 127 || c < -128)
		return (NULL);
	ptr = s;
	while (*ptr && *ptr != (char)c)
		++ptr;
	if (*ptr != (char)c)
		return (NULL);
	return (ptr);
}

#endif
