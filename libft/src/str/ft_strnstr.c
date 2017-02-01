/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/19 00:36:24 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#if !defined(NORM_LIBFT) || NORM_LIBFT == 1

/*
** norm libft, this function segfault on NULL pointers
*/

char	*ft_strnstr(char *str1, char *str2, size_t n)
{
	size_t	j;
	size_t	i;

	if (!*str2)
		return (str1);
	i = -1;
	while (++i < n && str1[i] && !(j = 0))
		while (str2[j] == str1[j + i])
			if (i + j++ < n && !str2[j])
				return (str1 + i);
	return (0);
}

#else

/*
** Other norm: will return NULL if str1 or str2 is NULL
*/

char	*ft_strnstr(char *str1, char *str2, size_t n)
{
	size_t	j;
	size_t	i;

	if (str1 == NULL || str2 == NULL)
		return (NULL);
	if (!*str2)
		return (str1);
	i = -1;
	while (++i < n && str1[i] && !(j = 0))
		while (str2[j] == str1[j + i])
			if (i + j++ < n && !str2[j])
				return (str1 + i);
	return (0);
}

#endif
