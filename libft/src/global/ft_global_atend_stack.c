/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_global_atend_stack.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 15:53:10 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/27 16:14:40 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_pile	*ft_global_atend_stack(void)
{
	static void		*data[FT_GLOBAL_ATEND_STACK_SIZE] = {0};
	static t_pile	stack = {.data = data,

	.size = FT_GLOBAL_ATEND_STACK_SIZE, .head = 0};
	return (&stack);
}
