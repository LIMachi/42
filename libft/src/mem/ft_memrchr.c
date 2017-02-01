/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 07:34:27 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/25 07:49:44 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memrchr(const void *s, int c, size_t n)
{
	while (n && ((unsigned char *)s)[n - 1] != (unsigned char)c)
		--n;
	return ((n && ((unsigned char *)s)[n - 1] == (unsigned char)c) ?
														(void *)(s + n) : NULL);
}
