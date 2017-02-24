/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/18 23:34:12 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char					*ft_itoa_base(int n, const int size_base,
															const char *base)
{
	unsigned int	v;
	int				len;
	char			*out;

	len = 2;
	v = (n < 0 && ++len) ? (unsigned int)-((long long)n) : (unsigned int)n;
	while (v /= size_base)
		++len;
	if ((out = (char *)ft_malloc(sizeof(char) * len)) == NULL)
		return (NULL);
	v = n < 0 ? (unsigned int)-((long long)n) : (unsigned int)n;
	out[--len] = '\0';
	if (!v)
		out[--len] = base[0];
	while (v)
	{
		out[--len] = base[v % size_base];
		v /= size_base;
	}
	if (n < 0)
		out[0] = '-';
	return (out);
}
