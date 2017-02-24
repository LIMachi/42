/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_conv_b.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/14 12:04:11 by hmarot            #+#    #+#             */
/*   Updated: 2016/09/26 13:30:48 by hmarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	prf_conv_mod(t_penv *env, va_list ap)
{
	if (ap == NULL)
		ap = NULL;
	env->flag & LESS ? 0 : prf_pos_field(env, 1);
	push_buff('%', env);
	env->flag & LESS ? prf_pos_field(env, 1) : 0;
}

void	prf_con_s(t_penv *env, va_list ap)
{
	char	*str;
	int		i;
	int		j;
	int		len;

	i = 0;
	env->modif = 3;
	str = (char *)prf_u_arg(ap, *env);
	str == NULL ? str = "(null)" : 0;
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

void	prf_con_ls(t_penv *env, va_list ap)
{
	wchar_t	*str;
	int		i;
	int		j;
	int		size;
	int		len;

	i = 0;
	size = 0;
	env->modif = 3;
	str = (wchar_t *)prf_u_arg(ap, *env);
	if (str == NULL)
	{
		return_null(env);
		return ;
	}
	len = prf_strlen_uni(str);
	env->pressi == -1 ? env->pressi = len : 0;
	j = len < env->pressi ? len : env->pressi;
	env->flag & LESS ? 0 : prf_pos_field(env, j);
	while (str[i] && (size < env->pressi || env->pressi == -1))
	{
		size += push_uni(str[i], env, nb_len_b(str[i], 2));
		++i;
	}
	env->flag & LESS ? prf_pos_field(env, j) : 0;
}

void	prf_con_p(t_penv *env, va_list ap)
{
	env->modif = 3;
	env->flag |= SHARP;
	prf_con_x(env, ap);
}

void	prf_con_ld(t_penv *env, va_list ap)
{
	env->modif = 3;
	prf_con_id(env, ap);
}
