/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/21 02:37:23 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_putendl(char const *s)
{
	ft_putstr(s);
	(void)(write(1, "\n", 1) == 1);
	if ((*ft_global_flags() & GF_FORCE_LOG) == GF_FORCE_LOG)
		ft_global_log(LOG_SET | LOG_STORE, (char[2]){'\n', '\0'});
}
