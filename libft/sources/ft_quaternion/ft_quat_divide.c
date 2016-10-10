/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quat_divide.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 0000/00/00 00:00:00 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/06 23:57:49 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_quaternion	ft_quat_divide(const t_quaternion a, const t_quaternion b)
{
	return (ft_quat_multiply(a, ft_quat_inverse(b)));
}
