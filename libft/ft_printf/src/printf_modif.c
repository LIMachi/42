/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_modif.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/14 12:04:11 by hmarot            #+#    #+#             */
/*   Updated: 2016/06/19 11:28:59 by hmarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		prf_modif(char *form, int i, t_penv *env)
{
	if (form[i] == 'h' && form[i + 1] == 'h')
		env->modif = 1;
	else if (form[i] == 'h')
		env->modif = 2;
	else if (form[i] == 'l' || form[i] == 'j' || form[i] == 'z')
		env->modif = 3;
	while (char_chr(form[i], "hljz") != -1)
		++i;
	return (i);
}
