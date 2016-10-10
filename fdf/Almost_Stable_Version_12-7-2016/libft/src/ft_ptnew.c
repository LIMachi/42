/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptnew.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 04:27:59 by hmartzol          #+#    #+#             */
/*   Updated: 2016/02/10 04:30:21 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_point	*ft_ptnew(int x, int y)
{
	t_point *out;

	if ((out = (t_point*)malloc(sizeof(t_point))) == NULL)
		return (NULL);
	out->x = x;
	out->y = y;
	return (out);
}
