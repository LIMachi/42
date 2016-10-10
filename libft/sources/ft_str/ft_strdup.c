/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/08/10 10:57:13 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strdup(const char *s1)
{
	char	*out;
	int		len;

	len = ft_strlen(s1) + 1;
	if ((out = (char*)malloc(sizeof(char) * len)) == NULL)
		return (NULL);
	return ((char *)ft_memcpy(out, (void *)s1, len));
}

char	*ft_strndup(const char *s1, const int end)
{
	char	*out;
	int		len;

	len = ft_strlen(s1) + 1;
	if (end < len)
		len = end;
	if ((out = (char*)ft_memalloc(sizeof(char) * len)) == NULL)
		return (NULL);
	return ((char *)ft_memcpy(out, (void *)s1, len - 1));
}
