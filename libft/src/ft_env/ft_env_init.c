/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 18:22:20 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/17 14:19:19 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** takes NULL or a pointer to a list of string containing environement variables
** and will initialise ft_global_env with it (actually, with a NULL env, will
** just return 0)
*/

int	ft_env_init(char **env)
{
	if (env == NULL)
		return (0);
	while (*env)
		if (ft_putenv(*env++) == -1)
			return (-1);
	return (0);
}
