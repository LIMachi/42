/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/14 14:11:21 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	if (!n)
		return (0);
	if (*s1 == *s2)
	{
		if (*s1 == 0)
			return (0);
		else
			return (ft_strncmp(s1 + 1, s2 + 1, n - 1));
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
