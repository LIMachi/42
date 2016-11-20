/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 20:14:49 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/20 18:51:04 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_init(char **env)
{
	if (ft_global_log(LOG_SET_PATH, DEFAULT_LOG_PATH) == NULL ||
			ft_global_log(LOG_SET | LOG_STORE, "New log started\n") == NULL)
		(void)ft_error(ERROR_ERRNO, 0);
	ft_env_init(env);
}
