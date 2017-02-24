/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 17:05:41 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/19 00:39:11 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strpdup(const char *s, const char *e)
{
	char	*out;
	size_t	size;

	if (s == NULL || e == NULL || s > e)
		return (NULL);
	size = (size_t)(e - s);
	if ((out = (char*)ft_malloc(++size * sizeof(char))) == NULL)
		return (NULL);
	out[--size] = '\0';
	while (size--)
		out[size] = s[size];
	return (out);
}
