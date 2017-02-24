/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_end.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 20:14:49 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/08 23:17:45 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static inline void	sf_endcalls(void)
{
	void	(*func)();
	t_pile	*stack;

	stack = ft_global_atend_stack();
	while (stack->head > 0)
	{
		func = NULL;
		(void)ft_pile_pull(stack, (void**)&func);
		if (func != NULL)
			func();
	}
}

#if !defined(FT_USE_FINAL_FREE) || FT_USE_FINAL_FREE == 0

void				ft_end(int r)
{
	if (ft_global_atend_stack()->head > 0)
		sf_endcalls();
	ft_env_clear();
	if (ft_global_log(LOG_SET | LOG_STORE, "Log ended\n") == NULL)
		ft_error(ERROR_ERRNO, 0);
	ft_global_log(LOG_END, NULL);
	EXIT(r);
}

#else

void				ft_end(int r)
{
	if (ft_global_atend_stack()->head > 0)
		sf_endcalls();
	ft_env_clear();
	if (ft_global_log(LOG_SET | LOG_STORE, "Log ended\n") == NULL)
		ft_error(ERROR_ERRNO, 0);
	ft_global_log(LOG_END, NULL);
	*ft_global_flags() = 0;
	ft_final_free();
	EXIT(r);
}

#endif
