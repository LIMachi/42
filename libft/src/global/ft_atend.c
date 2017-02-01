/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atend.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 16:02:50 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/07 18:38:56 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** similar to atexit (ISO C90), store functions in a stack to call them at
** ft_end() call (atexit call stored function on exit() call)
** note: all calls will be made before internal ending calls to env, error, log,
** and eventual final free, so functions can still call env acces, malloc, free
** error and log
** return 0 on succes or -1 and call ft_error with ENOMEM if the stacking failed
** the default stack is 32 functions, but this can be expanded via redefinition
** of FT_GLOBAL_ATEND_STACK_SIZE in libft.h
*/

int	ft_atend(void (*func)(void))
{
	if (ft_pile_push(ft_global_atend_stack(), func) == NULL)
		return (-1 + (int)ft_error(ENOMEM, "ft_atend stacking call failed: "));
	return (0);
}
