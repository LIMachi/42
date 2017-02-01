/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stracat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 17:03:10 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/22 02:49:02 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_stracat(char *str1, char *str2)
{
	size_t	size;
	char	*out;
	char	*ptr;

	if (str1 == NULL && str2 == NULL)
		return (NULL);
	if (str1 == NULL)
		return (ft_strndup(str2, ft_strlen(str2)));
	if (str2 == NULL)
		return (ft_strndup(str1, ft_strlen(str1)));
	size = ft_strlen(str1) + ft_strlen(str2) + 1;
	if ((out = (char*)ft_malloc(size * sizeof(char))) == NULL)
		return (NULL);
	ptr = out;
	while (*str1)
		*ptr++ = *str1++;
	while (*str2)
		*ptr++ = *str2++;
	*ptr = '\0';
	return (out);
}
