/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 15:41:37 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/18 15:16:56 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include "ft_float.h"

/*
** takes __T_FLOAT (float or double, deppending on flags passed at compilation),
** a precision and try to write in ascii f in buff if buff is non-null. if
** buff is null, ft_dtoa will try to allocate a string big enougth to contain
** f. if writen is non-null, after return, writen will have the total characters
** writen to buff, or the size of buff if buff was null at call.
** return a pointer to buff (either buff itself or the newly allocated buffer)
** return NULL on error and writen will have the characters actually writen in
** buff
*/

inline static void	sf_dtoa()
{

}

char	*ft_dtoa(__T_FLOAT f, int precision, char *buff, int *writen)
{
	t_float			v;
	__T_FLOAT_I		expo;
	__T_FLOAT_UI	mant;
	__T_FLOAT_UI	frac;
	__T_FLOAT_UI	mask;

	if (!(f == f))
	{
		write(1, "nan", 3);
		return (NULL);
	}
	v = (t_float){.f = f};
	if (v.part.sign && !(v.part.sign == 0))
		write(1, "-", 1);
	if (v.part.exp == __INFINITY_EXP)
	{
		write(1, "inf", 3);
		return (NULL);
	}
	if (v.part.exp == 0) //subnormal numbers
	{
		write(1, "0", 1);
		return (NULL);
	}
	mant = v.part.mant | __T_FLOAT_MANT_COMP;
	expo = v.part.exp - __T_FLOAT_EXP_BIAS;
	frac = 0;
	mask = ((__T_FLOAT_UI)-1) >> (__T_FLOAT_BSIZE - __T_FLOAT_MANT_SIZE - 1);
	if (expo > __T_FLOAT_EXP_BIAS || expo <= -__T_FLOAT_EXP_BIAS)
		return (NULL);
	else if (expo >= __T_FLOAT_MANT_SIZE)
		printf("%llu", (uint64_t)(mant << (expo - __T_FLOAT_MANT_SIZE)));
	else if (expo >= 0)
	{
		printf("%llu", (uint64_t)(mant >> (__T_FLOAT_MANT_SIZE - expo)));
		frac = (mant << (expo + 1)) & mask;
	}
	else
	{
		printf("0");
		frac = ((mant & mask) >> -(expo + 1));
	}
	if (precision > 0)
	{
		printf(".");
		while (!(0 * (frac *= 10)) && --precision >= 0)
		{
			printf("%c", (int)(frac >> (__T_FLOAT_MANT_SIZE + 1)) + '0');
			frac &= mask;
		}
		//still needs rounding
	}
	return (buff);
}
