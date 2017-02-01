/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/19 00:25:07 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*out;
	int		i;

	if (s == NULL || f == NULL)
		return (NULL);
	if ((out = (char *)ft_malloc(sizeof(char) * (ft_strlen(s) + 1))) == NULL)
		return (NULL);
	i = -1;
	while (s[++i])
		out[i] = (*f)(s[i]);
	out[i] = 0;
	return (out);
}
