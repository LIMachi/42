/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/02/08 19:52:11 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strstr(char *str1, char *str2)
{
	char *p_tmp;

	if (!*str2)
		return (str1);
	p_tmp = str1;
	while ((p_tmp = ft_strchr(p_tmp, (int)*str2)))
	{
		if (!ft_memcmp(str2, p_tmp, ft_strlen(str2)))
			return (p_tmp);
		++p_tmp;
	}
	return (NULL);
}
