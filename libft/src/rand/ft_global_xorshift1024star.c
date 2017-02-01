/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_global_xorshift1024star.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 08:57:50 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/24 09:40:11 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_xorshift1024star	*ft_global_xorshift1024star(void)
{
	static t_xorshift1024star	s = {.p = 0, .s = {0}};

	return (&s);
}
