/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quat_equal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 11:27:35 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/02 11:29:22 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

inline int	ft_quat_equal(const t_quaternion a, const t_quaternion b)
{
	return (a.r == b.r && a.i == b.i && a.j == b.j && a.k == b.k);
}
