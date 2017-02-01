/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_conv_c.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/14 12:04:11 by hmarot            #+#    #+#             */
/*   Updated: 2016/04/05 10:18:20 by hmarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	prf_con_id(t_penv *env, va_list ap)
{
	long	arg;
	int		len;
	int		i;

	arg = prf_arg(ap, *env);
	env->pressi == 0 && arg == 0 ? env->field++ : 0;
	len = nb_len(arg);
	i = len < env->pressi ? env->pressi : len;
	env->flag & ZERO ? aply_signe(arg, env) : 0;
	env->flag & LESS ? 0 : prf_pos_field(env, i + (arg < 0 || env->flag & MORE\
	|| env->flag & SPACE));
	env->flag & ZERO ? 0 : aply_signe(arg, env);
	prf_pos_pressi(env, len);
	env->pressi == 0 && arg == 0 ? 0 : prf_itoa(arg, env);
	env->flag & LESS ? prf_pos_field(env, i + (arg < 0 || env->flag & MORE\
	|| env->flag & SPACE)) : 0;
}

void	prf_con_o(t_penv *env, va_list ap)
{
	unsigned long	arg;
	int				len;
	int				i;

	arg = prf_u_arg(ap, *env);
	env->pressi == 0 && arg == 0 ? env->field++ : 0;
	len = nb_len_b(arg, 8);
	env->flag & SHARP && env->pressi != 0 ? --env->pressi : 0;
	i = len < env->pressi ? env->pressi : len;
	env->flag & ZERO ? aply_sharp(env, 3 * (env->flag & SHARP)) : 0;
	env->flag & LESS ? 0 : prf_pos_field(env, i + (env->flag & SHARP));
	env->flag & ZERO ? 0 : aply_sharp(env, 3 * (env->flag & SHARP));
	prf_pos_pressi(env, len);
	env->pressi == 0 && arg == 0 ? 0 : prf_itoa_b(arg, env, 8, 0);
	env->flag & LESS ? prf_pos_field(env, i + (env->flag & SHARP)) : 0;
}

void	prf_con_lo(t_penv *env, va_list ap)
{
	env->modif = 3;
	prf_con_o(env, ap);
}

void	prf_con_u(t_penv *env, va_list ap)
{
	unsigned long	arg;
	int				len;
	int				i;

	arg = prf_u_arg(ap, *env);
	env->pressi == 0 && arg == 0 ? env->field++ : 0;
	len = nb_len_b(arg, 10);
	i = len < env->pressi ? env->pressi : len;
	env->flag & LESS ? 0 : prf_pos_field(env, i);
	prf_pos_pressi(env, len);
	env->pressi == 0 && arg == 0 ? 0 : prf_itoa_b(arg, env, 10, 0);
	env->flag & LESS ? prf_pos_field(env, i) : 0;
}

void	prf_con_lu(t_penv *env, va_list ap)
{
	env->modif = 3;
	prf_con_u(env, ap);
}
