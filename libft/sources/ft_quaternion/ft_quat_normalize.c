/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quat_normalize.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 0000/00/00 00:00:00 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/06 23:59:51 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_quaternion	ft_quat_normalize(const t_quaternion q)
{
	return (ft_quat_scale(q, 1 / ft_quat_norm(q)));
}
