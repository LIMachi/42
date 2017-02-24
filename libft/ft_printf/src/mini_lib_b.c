/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_lib_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarot <hmarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/14 12:04:11 by hmarot            #+#    #+#             */
/*   Updated: 2017/02/01 15:01:08 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	push_buff(char c, t_penv *env)
{
	if (env->pos < BUFF_SIZE)
	{
		env->buffer[env->pos] = c;
		++(env->pos);
	}
	else
	{
		ft_void(write(1, env->buffer, BUFF_SIZE));
		env->ret += env->pos;
		env->pos = 0;
		push_buff(c, env);
	}
}

int		push_uni(wchar_t c, t_penv *env, int nbbi)
{
	if (nbbi >= 1 && nbbi <= 7)
		push_buff(c, env);
	else if (nbbi >= 8 && nbbi <= 11)
	{
		push_buff(((3 << 6) | (c >> 6)), env);
		push_buff(((1 << 7) | (63 & c)), env);
		return (2);
	}
	else if (nbbi >= 12 && nbbi <= 16)
	{
		push_buff((7 << 5) | (c >> 12), env);
		push_buff((1 << 7) | (63 & (c >> 6)), env);
		push_buff((1 << 7) | (63 & c), env);
		return (3);
	}
	else if (nbbi >= 17 && nbbi <= 21)
	{
		push_buff((15 << 4) | (c >> 18), env);
		push_buff((1 << 7) | (63 & (c >> 12)), env);
		push_buff((1 << 7) | (63 & (c >> 6)), env);
		push_buff((1 << 7) | (63 & c), env);
		return (4);
	}
	return (1);
}

int		prf_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}

int		prf_strlen_uni(wchar_t *str)
{
	int		i;
	int		ret;
	int		nbbi;

	i = 0;
	ret = 0;
	while (str[i])
	{
		nbbi = nb_len_b(str[i], 2);
		if (nbbi >= 1 && nbbi <= 7)
			++ret;
		else if (nbbi >= 8 && nbbi <= 11)
			ret += 2;
		else if (nbbi >= 12 && nbbi <= 16)
			ret += 3;
		else if (nbbi >= 17 && nbbi <= 21)
			ret += 4;
		++i;
	}
	return (ret);
}

int		char_chr(char c, char *chr)
{
	int		i;

	i = 0;
	while (chr[i])
	{
		if (c == chr[i])
			return (i);
		++i;
	}
	return (-1);
}
