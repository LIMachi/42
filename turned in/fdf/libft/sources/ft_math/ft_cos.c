/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 13:23:27 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/06 22:38:17 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#if defined(_MATH_H) && _MATH_H == 1

double	ft_cos(double x)
{
	return (cos(x));
}

#else

double	ft_cos(double x)
{
	return (ft_sin(RADIAN(90 - DEGRE(x))));
}

#endif
