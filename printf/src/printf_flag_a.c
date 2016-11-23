/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_flag_a.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 05:25:05 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/23 05:25:07 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	prf_flag_sharp(t_env *env)
{
	env->flag |= SHARP;
}

void	prf_flag_zero(t_env *env)
{
	if ((env->flag & LESS) == 0)
		env->flag |= ZERO;
}

void	prf_flag_less(t_env *env)
{
	env->flag &= ~ZERO;
	env->flag |= LESS;
}

void	prf_flag_more(t_env *env)
{
	env->flag &= ~SPACE;
	env->flag |= MORE;
}

void	prf_flag_space(t_env *env)
{
	if ((env->flag & MORE) == 0)
		env->flag |= SPACE;
}
