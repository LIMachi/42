/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_conv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarot <hmarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/14 12:04:11 by hmarot            #+#    #+#             */
/*   Updated: 2017/01/22 03:32:41 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		prf_conv(char *format, int i, t_penv *env, va_list ap)
{
	int		j;
	void	(*tab_conv[15])(t_penv *env, va_list ap);

	tab_conv[0] = prf_conv_mod;
	tab_conv[1] = prf_con_id;
	tab_conv[2] = prf_con_id;
	tab_conv[3] = prf_con_ld;
	tab_conv[4] = prf_con_u;
	tab_conv[5] = prf_con_x;
	tab_conv[6] = prf_con_lx;
	tab_conv[7] = prf_con_o;
	tab_conv[8] = prf_con_lo;
	tab_conv[9] = prf_con_lu;
	tab_conv[10] = prf_con_p;
	tab_conv[11] = prf_con_s;
	tab_conv[12] = prf_con_c;
	tab_conv[13] = prf_con_lc;
	tab_conv[14] = prf_con_ls;
	j = char_chr(format[i], "%idDuxXoOUpscCS");
	if (j == -1)
		return (-1);
	tab_conv[j](env, ap);
	return (i);
}
