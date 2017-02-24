/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/14 12:04:11 by hmarot            #+#    #+#             */
/*   Updated: 2016/06/19 11:27:56 by hmarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

unsigned long	prf_u_arg(va_list ap, t_penv env)
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

long			prf_arg(va_list ap, t_penv env)
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
