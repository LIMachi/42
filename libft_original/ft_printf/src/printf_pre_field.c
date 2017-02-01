/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_pre_field.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 05:27:07 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/23 05:27:24 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		prf_pressi(char *form, int i, t_env *env)
{
	int		j;

	if (form[i] == '.')
	{
		env->flag &= ~ZERO;
		env->pressi = 0;
		++i;
		while ((j = char_chr(form[i], "0123456789")) != -1)
		{
			env->pressi *= 10;
			env->pressi += j;
			++i;
		}
	}
	return (i);
}

void	prf_pos_pressi(t_env *env, int len)
{
	if (env->pressi != -1)
	{
		while (len < env->pressi)
		{
			push_buff('0', env);
			--env->pressi;
		}
	}
}

int		prf_field(char *form, int i, t_env *env)
{
	int		j;

	while ((j = char_chr(form[i], "0123456789")) != -1)
	{
		env->field *= 10;
		env->field += j;
		++i;
	}
	return (i);
}

void	prf_pos_field(t_env *env, int len)
{
	while (len < env->field)
	{
		push_buff(env->flag & ZERO ? '0' : ' ', env);
		--env->field;
	}
}
