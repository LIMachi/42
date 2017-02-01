/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/19 00:29:21 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#if !defined(NORM_LIBFT) || NORM_LIBFT == 1

/*
** norm libft, this function segfault on NULL pointers
*/

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	if (n == 0)
		return (0);
	if (*s1 == *s2)
	{
		if (*s1 == 0)
			return (0);
		else
			return (ft_strncmp(s1 + 1, s2 + 1, n - 1));
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

#else

/*
** Other norm: will treat NULL pointed string has string starting with '\0', and
** so it will return 0 on a comparaison between two NULL pointed string.
** Non standard.
*/

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	if (n == 0)
		return (0);
	if (s1 == NULL && s2 == NULL)
		return (0);
	if (s1 == NULL || s2 == NULL)
	{
		if (s1 == NULL)
			return ('\0' - *s2);
		else
			return (*s1 - '\0');
	}
	if (*s1 == *s2)
	{
		if (*s1 == 0)
			return (0);
		else
			return (ft_strncmp(s1 + 1, s2 + 1, n - 1));
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

#endif
