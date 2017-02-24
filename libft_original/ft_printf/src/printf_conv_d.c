/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_conv_d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 05:18:44 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/23 05:18:47 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	prf_con_x(t_env *env, va_list ap)
{
	unsigned long	arg;
	int				len;
	int				i;

	arg = prf_u_arg(ap, *env);
	env->pressi == 0 && arg == 0 ? env->field++ : 0;
	len = nb_len_b(arg, 16);
	i = len < env->pressi ? env->pressi : len;
	env->flag & ZERO && arg != 0 ? aply_sharp(env, (env->flag & SHARP)) : 0;
	env->flag & LESS ? 0 : prf_pos_field(env, i + (2 * (env->flag & SHARP)));
	env->flag & ZERO || arg == 0 ? 0 : aply_sharp(env, (env->flag & SHARP));
	prf_pos_pressi(env, len);
	env->pressi == 0 && arg == 0 ? 0 : prf_itoa_b(arg, env, 16, 0);
	env->flag & LESS ? prf_pos_field(env, i + (2 * (env->flag & SHARP))) : 0;
}

void	prf_con_lx(t_env *env, va_list ap)
{
	unsigned long	arg;
	int				len;
	int				i;

	arg = prf_u_arg(ap, *env);
	len = nb_len_b(arg, 16);
	i = len < env->pressi ? env->pressi : len;
	env->flag & ZERO && arg != 0 ? aply_sharp(env, 2 * (env->flag & SHARP)) : 0;
	env->flag & LESS ? 0 : prf_pos_field(env, i + (2 * (env->flag & SHARP)));
	env->flag & ZERO || arg == 0 ? 0 : aply_sharp(env, 2 * (env->flag & SHARP));
	prf_pos_pressi(env, len);
	prf_itoa_b(arg, env, 16, 1);
	env->flag & LESS ? prf_pos_field(env, i + (2 * (env->flag & SHARP))) : 0;
}

void	prf_con_c(t_env *env, va_list ap)
{
	char	c;

	env->modif = 1;
	c = (char)prf_arg(ap, *env);
	env->flag & LESS ? 0 : prf_pos_field(env, 1);
	push_buff(c, env);
	env->flag & LESS ? prf_pos_field(env, 1) : 0;
}

void	prf_con_lc(t_env *env, va_list ap)
{
	wchar_t	c;

	env->modif = 0;
	c = (wchar_t)prf_arg(ap, *env);
	env->flag & LESS ? 0 : prf_pos_field(env, 1);
	push_uni(c, env, nb_len_b(c, 2));
	env->flag & LESS ? prf_pos_field(env, 1) : 0;
}

void	return_null(t_env *env)
{
	char	*str;
	int		i;
	int		j;
	int		len;

	i = 0;
	env->modif = 3;
	str = "(null)";
	len = prf_strlen(str);
	env->pressi == -1 ? env->pressi = len : 0;
	j = len < env->pressi ? len : env->pressi;
	env->flag & LESS ? 0 : prf_pos_field(env, j);
	while (str[i] && (i < env->pressi || env->pressi == -1))
	{
		push_buff(str[i], env);
		++i;
	}
	env->flag & LESS ? prf_pos_field(env, j) : 0;
}
