/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/14 09:17:00 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_itoa(int c)
{
	char	*out;
	int		len;
	int		n;

	if (c == -2147483648)
		return (ft_strdup("-2147483648"));
	len = 2 + (c < 0);
	n = c < 0 ? -c : c;
	while (n /= 10)
		++len;
	if ((out = (char *)ft_malloc(sizeof(char) * len)) == NULL)
		return (NULL);
	n = c < 0 ? -c : c;
	out[--len] = 0;
	if (!n)
		out[--len] = '0';
	while (n)
	{
		out[--len] = n % 10 + '0';
		n /= 10;
	}
	if (c < 0)
		out[0] = '-';
	return (out);
}
