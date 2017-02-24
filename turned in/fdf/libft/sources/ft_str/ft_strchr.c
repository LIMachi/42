/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/03 17:21:33 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#if defined(NORM_42) && (NORM_42 < 1)

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

#else

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

#endif
