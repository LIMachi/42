/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_flag.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/14 12:04:11 by hmarot            #+#    #+#             */
/*   Updated: 2016/04/05 10:18:20 by hmarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		prf_flag(char *form, int i, t_penv *env)
{
	int		j;
	void	(*tab_conv[5])(t_penv *env);

	tab_conv[0] = prf_flag_sharp;
	tab_conv[1] = prf_flag_zero;
	tab_conv[2] = prf_flag_less;
	tab_conv[3] = prf_flag_more;
	tab_conv[4] = prf_flag_space;
	while ((j = char_chr(form[i], "#0-+ ")) != -1)
	{
		tab_conv[j](env);
		++i;
	}
	return (i);
}
