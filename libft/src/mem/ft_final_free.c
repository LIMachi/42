/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_final_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 01:24:49 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/08 23:24:43 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** this function will try to free any pointer in ft_global_malloc_stack()
** calling this function will free any memory allocated by ft_malloc, avoiding
** final leaks, but calling this function prior to a ft_free or free can make
** double free, use this function only at end of program or let it be called
** by ft_end()
*/

#if !defined(FT_USE_FINAL_FREE) || FT_USE_FINAL_FREE == 0

/*
** if ft_final_free() is called but the macro FT_USE_FINAL_FREE is unset
** (meaning ft_final_free() is disabled), it will log an explicit message
** instead of accessing ft_global_malloc_stack()
*/

void	ft_final_free(void)
{
	ft_log("ft_final_free is disabled, FT_USE_FINAL_FREE is unset\n");
}

#else

# if 0

void	ft_final_free(void)
{
	void	*ptr;

	while ((ptr = ft_global_malloc_stack(FT_STACK_POP, NULL)) != NULL)
		ft_free(ptr);
}

# else

#  if !defined(FT_LOG_FINAL_FREE) || FT_LOG_FINAL_FREE == 0

void	ft_final_free(void)
{
	size_t	i;

	i = 0;
	while (i < ft_global_malloc_stack()->head)
		if (ft_global_malloc_stack()->data[i++] != NULL)
		{
			free(ft_global_malloc_stack()->data[i - 1]);
			ft_global_malloc_stack()->data[i - 1] = NULL;
		}
	ft_global_malloc_stack()->head = 0;
}

#  else

void	ft_final_free(void)
{
	size_t	i;

	i = 0;
	while (i < ft_global_malloc_stack()->head)
		if (ft_global_malloc_stack()->data[i++] != NULL)
		{
			ft_void(write(1, "final-freed pointer: ", 21));
			ft_putnbr_hex((unsigned long)ft_global_malloc_stack()->data[i - 1]);
			ft_void(write(1, "\n", 1));
			free(ft_global_malloc_stack()->data[i - 1]);
			ft_global_malloc_stack()->data[i - 1] = NULL;
		}
	ft_global_malloc_stack()->head = 0;
}

#  endif

# endif

#endif
