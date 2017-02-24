/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_global_malloc_stack.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 01:07:06 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/27 16:00:50 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#if !defined(FT_USE_FINAL_FREE) || FT_USE_FINAL_FREE == 0

/*
** if ft_global_malloc_stack() is called but the macro FT_USE_FINAL_FREE is
** unset (meaning ft_global_malloc_stack() is disabled), it will log an
** explicit message instead of accessing ft_global_malloc_stack()
*/

t_pile	*ft_global_malloc_stack(void)
{
	ft_log("ft_global_malloc_stack is disabled, FT_USE_FINAL_FREE is unset\n");
	return (NULL);
}

#else

t_pile	*ft_global_malloc_stack(void)
{
	static void		*pile[FT_GLOBAL_MALLOC_STACK_SIZE] = {0};
	static t_pile	stack = {.data = pile,

	.size = FT_GLOBAL_MALLOC_STACK_SIZE, .head = 0};
	return (&stack);
}

#endif
