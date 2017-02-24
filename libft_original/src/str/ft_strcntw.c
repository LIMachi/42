/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcntw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 19:28:24 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/14 14:10:53 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_strcntw(char const *str)
{
	int	out;
	int	i;

	if (str == NULL)
		return (0);
	out = 0;
	i = 0;
	while (str[i])
		if (str[i] && !ft_isspace(str[i]))
		{
			++out;
			while (str[i] && !ft_isspace(str[i]))
				++i;
		}
		else
			while (ft_isspace(str[i]))
				++i;
	return (out);
}
