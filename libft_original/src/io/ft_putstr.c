/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/21 02:39:44 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_putstr(char const *s)
{
	if (s == NULL)
		return ;
	(void)(write(1, s, ft_strlen(s)) == 0);
	if ((*ft_global_flags() & GF_FORCE_LOG) == GF_FORCE_LOG)
		ft_global_log(LOG_SET | LOG_STORE, (char*)s);
}
