/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 22:42:39 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/05 15:06:49 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	*ft_range(int min, int max)
{
	int	*out;
	int	i;

	if (max <= min)
		return (NULL);
	out = (int*)malloc(sizeof(int) * (max - min));
	i = -1;
	while (++i < (max - min))
		out[i] = i + min;
	return (out);
}
