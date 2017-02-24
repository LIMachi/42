/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_lib_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 04:49:18 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/23 04:49:21 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	aply_signe(long nb, t_env *env)
{
	if (nb < 0)
		push_buff('-', env);
	else if (env->flag & MORE)
		push_buff('+', env);
	else if (env->flag & SPACE)
		push_buff(' ', env);
}
