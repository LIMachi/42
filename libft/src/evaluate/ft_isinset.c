/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isinset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 18:18:24 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/13 18:28:43 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_isinset(const char c, const char *set)
{
	int	i;

	if (set == NULL)
		return (0);
	if (c == '\0')
		return (1);
	i = -1;
	while (set[++i] != '\0')
		if (c == set[i])
			return (1);
	return (0);
}
