/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 18:16:22 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/19 00:12:28 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t	ft_strcspn(const char *str, const char *reject)
{
	size_t	i;

	if (str == NULL)
		return (0);
	if (reject == NULL)
		return (ft_strlen(str));
	i = 0;
	while (!ft_isinset(str[i], reject))
		++i;
	return (i);
}
