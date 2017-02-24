/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 05:25:17 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/23 05:25:19 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	prf_init(t_env *env)
{
	env->flag = 0;
	env->pressi = -1;
	env->field = 0;
	env->modif = 0;
	env->pos = 0;
	env->ret = 0;
	env->err = 0;
}

void	prf_loop(t_env *env)
{
	env->flag = 0;
	env->pressi = -1;
	env->field = 0;
	env->modif = 0;
}
