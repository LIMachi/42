/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 22:24:35 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/05 15:06:14 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		ft_strlen(char *str)
{
	int	n;

	n = 0;
	while (str[n])
		++n;
	return (n);
}

char	*ft_strdup(char *src)
{
	char	*out;
	char	*ptr;

	out = (char*)malloc(ft_strlen(src) + 1);
	ptr = out;
	while (*src != '\0')
		*ptr++ = *src++;
	*ptr = '\0';
	return (out);
}
