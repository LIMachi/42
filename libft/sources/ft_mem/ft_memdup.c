/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/09 05:34:26 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memdup(const void *src, size_t n)
{
	void	*out;
	void	*dst;

	if ((out = malloc(n)) == NULL)
		return (NULL);
	dst = out;
	while (n--)
		*(unsigned char*)dst++ = *(unsigned char*)src++;
	return (out);
}
