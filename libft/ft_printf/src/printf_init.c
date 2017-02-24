/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/14 12:04:11 by hmarot            #+#    #+#             */
/*   Updated: 2016/06/19 11:28:38 by hmarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	prf_init(t_penv *env)
{
	env->flag = 0;
	env->pressi = -1;
	env->field = 0;
	env->modif = 0;
	env->pos = 0;
	env->ret = 0;
	env->err = 0;
}

void	prf_loop(t_penv *env)
{
	env->flag = 0;
	env->pressi = -1;
	env->field = 0;
	env->modif = 0;
}
