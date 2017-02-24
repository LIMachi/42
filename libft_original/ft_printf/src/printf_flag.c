/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_flag.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 05:19:11 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/23 05:19:13 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		prf_flag(char *form, int i, t_env *env)
{
	int		j;
	void	(*tab_conv[5])(t_env *env);

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
