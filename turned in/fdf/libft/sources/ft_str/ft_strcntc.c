/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcntc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 19:28:24 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/14 14:10:51 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_strcntc(char const *str, char c)
{
	int	out;
	int	i;

	if (str == NULL)
		return (0);
	out = 0;
	i = 0;
	while (str[i])
		if (str[i++] == c)
			++out;
	return (out);
}
