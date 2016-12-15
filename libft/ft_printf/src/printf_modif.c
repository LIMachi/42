/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_modif.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 05:26:36 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/23 05:26:39 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		prf_modif(char *form, int i, t_env *env)
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
