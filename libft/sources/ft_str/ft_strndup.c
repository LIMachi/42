/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 17:02:21 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/03 17:02:38 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#if defined(NORM_42) && (NORM_42 < 1)

char	*ft_strndup(const char *s, size_t n)
{
	char	*out;

	if (s == NULL)
		return (NULL);
	if ((out = (char*)malloc(++n * sizeof(char))) == NULL)
		return (NULL);
	out[--n] = '\0';
	while (n--)
		out[n] = s[n];
	return (out);
}

#else

char	*ft_strndup(const char *s, size_t n)
{
	char	*out;

	if ((out = (char*)malloc(++n * sizeof(char))) == NULL)
		return (NULL);
	out[--n] = '\0';
	while (n--)
		out[n] = s[n];
	return (out);
}

#endif
