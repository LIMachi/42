/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_void.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 14:56:22 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/01 14:59:45 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** function used to silence -Werror=unused-result in write and other kind of
** functions
*/

inline void	ft_void(long long voidable_content)
{
	(void)voidable_content;
}
