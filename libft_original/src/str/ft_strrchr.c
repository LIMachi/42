/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/19 00:51:56 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#if !defined(NORM_LIBFT) || NORM_LIBFT == 1

/*
** norm libft, this function segfault on NULL pointers and have bad result on
** c being truncated by a char cast
*/

char	*ft_strrchr(const char *str, int c)
{
	char	*p_tmp;

	p_tmp = (char *)str;
	while (*p_tmp)
		++p_tmp;
	while (p_tmp >= (char *)str)
		if (*p_tmp-- == c)
			return (p_tmp + 1);
	return (NULL);
}

#else

/*
** Other norm: will return NULL if s is NULL, or if c is not a char
** Protected against segfault, non standard
*/

char	*ft_strrchr(const char *str, int c)
{
	char	*p_tmp;

	if (str == NULL || c > 127 || c < -128)
		return (NULL);
	p_tmp = (char *)str;
	while (*p_tmp)
		++p_tmp;
	while (p_tmp >= (char *)str)
		if (*p_tmp-- == c)
			return (p_tmp + 1);
	return (NULL);
}

#endif
