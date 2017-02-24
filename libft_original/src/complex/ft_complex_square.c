/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_complex_square.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 19:23:03 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/08 19:23:31 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_complex	ft_complex_square(const t_complex z)
{
	return ((t_complex){z.r * z.r - z.i * z.i, 2 * z.r * z.i});
}
