/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bswap16.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/00/00 00:00:00 by hmartzol          #+#    #+#             */
/*   Updated: 2016/10/08 08:29:05 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

unsigned short int	ft_bswap16(const unsigned short int x)
{
	return (((x & 0xFF00) >> 8) | ((x & 0xFF) << 8));
}