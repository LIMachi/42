/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_global_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 09:25:10 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/14 09:26:24 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

uint64_t	*ft_global_flags(void)
{
	static uint64_t	flags = DEFAULT_FLAGS;

	return (&flags);
}
