/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_powi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 16:44:53 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/09 16:50:29 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_powi(int nbr, int exp)
{
	int	out;

	out = 1;
	while (exp > 0 && --exp)
		out *= nbr;
	while (exp < 0 && ++exp)
		out /= nbr;
	return (out);
}
