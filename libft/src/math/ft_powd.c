/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_powd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 16:49:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/09 16:50:24 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

double	ft_powd(double nbr, int exp)
{
	double	out;

	out = 1.0;
	while (exp > 0 && --exp)
		out *= nbr;
	while (exp < 0 && ++exp)
		out /= nbr;
	return (out);
}
