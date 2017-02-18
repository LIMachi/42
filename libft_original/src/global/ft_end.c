/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_end.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 20:14:49 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/18 23:41:03 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#if !defined(FT_USE_FINAL_FREE) || FT_USE_FINAL_FREE == 0

void	ft_end(int r)
{
	if (ft_global_log(LOG_SET | LOG_STORE, "Log ended\n") == NULL)
		ft_error(ERROR_ERRNO, 0);
	ft_global_log(LOG_END, NULL);
	ft_env_clear();
	EXIT(r);
}

#else

void	ft_end(int r)
{
	if (ft_global_log(LOG_SET | LOG_STORE, "Log ended\n") == NULL)
		ft_error(ERROR_ERRNO, 0);
	ft_global_log(LOG_END, NULL);
	ft_env_clear();
	ft_final_free();
	EXIT(r);
}

#endif