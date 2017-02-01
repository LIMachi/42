/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_flag_a.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/14 12:04:11 by hmarot            #+#    #+#             */
/*   Updated: 2016/04/05 10:18:20 by hmarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	prf_flag_sharp(t_penv *env)
{
	env->flag |= SHARP;
}

void	prf_flag_zero(t_penv *env)
{
	if ((env->flag & LESS) == 0)
		env->flag |= ZERO;
}

void	prf_flag_less(t_penv *env)
{
	env->flag &= ~ZERO;
	env->flag |= LESS;
}

void	prf_flag_more(t_penv *env)
{
	env->flag &= ~SPACE;
	env->flag |= MORE;
}

void	prf_flag_space(t_penv *env)
{
	if ((env->flag & MORE) == 0)
		env->flag |= SPACE;
}
