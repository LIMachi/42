/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/00/00 00:00:00 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/19 00:38:36 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** search the next word in str delimited by space-like characters
*/

#if !defined(NORM_LIBFT) || NORM_LIBFT == 1

/*
** norm libft, this function segfault on NULL pointers
*/

char	*ft_strnw(char *str)
{
	while (*str != '\0' && !ft_isspace(*str))
		++str;
	while (ft_isspace(*str))
		++str;
	return (str);
}

#else

/*
** Other norm: return NULL if str is NULL
*/

char	*ft_strnw(char *str)
{
	if (str == NULL)
		return (NULL);
	while (*str != '\0' && !ft_isspace(*str))
		++str;
	while (ft_isspace(*str))
		++str;
	return (str);
}

#endif
