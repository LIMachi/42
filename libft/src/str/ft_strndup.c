/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 17:02:21 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/19 00:33:53 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#if !defined(NORM_LIBFT) || NORM_LIBFT == 1

/*
** norm libft, this function segfault on NULL pointers
*/

char	*ft_strndup(const char *s, size_t n)
{
	char	*out;

	if ((out = (char*)ft_malloc(++n * sizeof(char))) == NULL)
		return (NULL);
	out[--n] = '\0';
	while (n--)
		out[n] = s[n];
	return (out);
}

#else

/*
** Other norm: return NULL if s is NULL
*/

char	*ft_strndup(const char *s, size_t n)
{
	char	*out;

	if (s == NULL)
		return (NULL);
	if ((out = (char*)ft_malloc(++n * sizeof(char))) == NULL)
		return (NULL);
	out[--n] = '\0';
	while (n--)
		out[n] = s[n];
	return (out);
}

#endif
