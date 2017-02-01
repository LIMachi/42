/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/14 12:04:11 by hmarot            #+#    #+#             */
/*   Updated: 2016/09/09 15:08:17 by hmarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		nb_len(long nb)
{
	long	tmp;
	int		i;

	tmp = nb < 0 ? -nb : nb;
	i = 1;
	while (tmp >= 10)
	{
		(tmp = tmp / 10);
		++i;
	}
	return (i);
}

void	aply_sharp(t_penv *env, int conv)
{
	if (conv == 1)
	{
		push_buff('0', env);
		push_buff('x', env);
	}
	else if (conv == 2)
	{
		push_buff('0', env);
		push_buff('X', env);
	}
	else if (conv == 3)
		push_buff('0', env);
}

int		nb_len_b(unsigned long nb, int b)
{
	double	tmp;
	int		i;

	tmp = nb;
	i = 1;
	while (tmp >= b)
	{
		(tmp = tmp / b);
		++i;
	}
	return (i);
}

void	prf_itoa(long nb, t_penv *env)
{
	long	tmp;

	tmp = nb % 10;
	if (nb >= 10 || nb <= -10)
		prf_itoa(nb / 10, env);
	push_buff(((tmp < 0 ? -tmp : tmp) + '0'), env);
}

void	prf_itoa_b(unsigned long nb, t_penv *env, int b, int maj)
{
	char	*base;

	base = maj == 0 ? "0123456789abcdef" : "0123456789ABCDEF";
	if (nb >= (unsigned long)b)
		prf_itoa_b(nb / b, env, b, maj);
	push_buff((base[nb % b]), env);
}
