/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_global_malloc_stack.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 01:07:06 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/18 23:41:58 by hmartzol         ###   ########.fr       */
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

#if 0
void	*ft_global_malloc_stack(int flag, void *ptr)
{
	static void		*stack[FT_GLOBAL_MALLOC_STACK_SIZE] = {NULL};
	static size_t	head = 0;
	void			*tmp;

	if (flag == FT_STACK_PUT)
	{
		if (head < FT_GLOBAL_MALLOC_STACK_SIZE - 1)
			return (stack[head++] = ptr);
		return (NULL);
	}
	if (flag == FT_STACK_POP)
	{
		if (head == 0)
			return (NULL);
		tmp = stack[--head];
		stack[head + 1] = NULL;
		return (tmp);
	}
	if (flag == FT_STACK_LOOK)
	{
		if (head == 0)
			return (NULL);
		return (stack[head - 1]);
	}
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
#endif
