/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/14 14:11:23 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	unsigned int i;

	i = 0;
	while (++i <= n && src[i - 1])
		dst[i - 1] = src[i - 1];
	if (i <= n)
		dst[i - 1] = 0;
	while (++i <= n)
		dst[i - 1] = 0;
	return (dst);
}
