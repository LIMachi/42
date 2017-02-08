/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_void.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 14:56:22 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/08 22:59:15 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** function used to silence -Werror=unused-result in write and other kind of
** functions
*/

#if COMPILER == CC_CLANG

/*
** since clang optimise the function, we need to make it harder
*/

inline void	ft_void(long long voidable_content)
{
	(void)(voidable_content | 0);
}

#else

/*
** gcc compliant function
*/

inline void	ft_void(long long voidable_content)
{
	(void)voidable_content;
}

#endif
