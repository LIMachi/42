/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rand.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 08:48:41 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/24 09:12:15 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#if RAND_MODE == XORSHIFT1024STAR

int	ft_rand(void)
{
	return ((int)ft_xorshift1024star());
}

#else

int	ft_rand(void)
{
	return (0);
}

#endif
