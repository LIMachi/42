/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 18:16:22 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/13 18:23:42 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t	ft_strcspn(const char *str, const char *reject)
{
	size_t	i;

	i = 0;
	while (!ft_isinset(str[i], reject))
		++i;
	return (i);
}
