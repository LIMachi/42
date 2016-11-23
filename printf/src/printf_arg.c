/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 04:49:42 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/23 04:49:44 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

unsigned long	prf_u_arg(va_list ap, t_env env)
{
	if (env.modif == 0)
		return (va_arg(ap, unsigned int));
	if (env.modif == 3)
		return (va_arg(ap, unsigned long));
	if (env.modif == 2)
		return ((unsigned long)(unsigned short)va_arg(ap, unsigned int));
	if (env.modif == 1)
		return ((unsigned long)(unsigned char)va_arg(ap, unsigned int));
	return (0);
}

long			prf_arg(va_list ap, t_env env)
{
	if (env.modif == 0)
		return (va_arg(ap, int));
	if (env.modif == 3)
		return (va_arg(ap, long));
	if (env.modif == 2)
		return ((long)(short)va_arg(ap, int));
	if (env.modif == 1)
		return ((long)(char)va_arg(ap, int));
	return (0);
}
