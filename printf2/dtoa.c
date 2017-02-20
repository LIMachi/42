/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 15:41:37 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/19 22:23:33 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_float.h"
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <libft.h>

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

size_t	ft_u64_evaluate_size(__UINT64_TYPE__ v)
{
	size_t	out;
	static const unsigned long long	log[20] = {1ull, 10ull, 100ull, 1000ull,

	10000ull, 100000ull, 1000000ull, 10000000ull, 100000000ull, 1000000000ull,
	10000000000ull, 100000000000ull, 1000000000000ull, 10000000000000ull,
	100000000000000ull, 1000000000000000ull, 10000000000000000ull,
	100000000000000000ull, 1000000000000000000ull, 10000000000000000000ull};
	if (v == 0)
		return (1);
	out = 1;
	while (out < 20 && v >= log[out])
		++out;
	return (out);
}

double	ft_pow10(int v)
{
	static const double	pow[51] = {0.0000000000000000000000001,

	0.000000000000000000000001, 0.00000000000000000000001,
	0.0000000000000000000001, 0.000000000000000000001, 0.00000000000000000001,
	0.0000000000000000001, 0.000000000000000001, 0.00000000000000001,
	0.0000000000000001, 0.000000000000001, 0.00000000000001, 0.0000000000001,
	0.000000000001, 0.00000000001, 0.0000000001, 0.000000001, 0.00000001,
	0.0000001, 0.000001, 0.00001, 0.0001, 0.001, 0.01, 0.1, 1.0, 10.0, 100.0,
	1000.0, 10000.0, 100000.0, 1000000.0, 10000000.0, 100000000.0, 1000000000.0,
	10000000000.0, 100000000000.0, 1000000000000.0, 10000000000000.0,
	100000000000000.0, 1000000000000000.0, 10000000000000000.0,
	100000000000000000.0, 1000000000000000000.0, 10000000000000000000.0,
	100000000000000000000.0, 1000000000000000000000.0,
	10000000000000000000000.0, 100000000000000000000000.0,
	1000000000000000000000000.0, 10000000000000000000000000.0};
	if (v > 25)
		return (10000000000000000000000000.0 * ft_pow10(v - 25));
	if (v < -25)
		return (0.00000000000000000000000001 * ft_pow10(v + 25));
	return (pow[25 + v]);
}



size_t	ft_float_evaluate_size(t_float v, int precision)
{
	size_t			out;
	__T_FLOAT_I		expo;
	__T_FLOAT_UI	mant;

	if (v.f != v.f)
		return (3);
	if (v.part.exp == __INFINITY_EXP)
		return (3 + v.part.sign);
	v.f += ft_pow10(-precision);	//add a little extra to avoid overflow on 99.9999... rounded to 100.0000...
	out = precision + 1;
	if (v.part.exp == 0 || (expo = v.part.exp - __T_FLOAT_EXP_BIAS) < 0)
		++out;
	else
	{
		mant = v.part.mant | __T_FLOAT_MANT_COMP;
		if (expo >= __T_FLOAT_MANT_SIZE)
			out += ft_u64_evaluate_size(mant << (expo - __T_FLOAT_MANT_SIZE));
		else
			out += ft_u64_evaluate_size(mant >> (__T_FLOAT_MANT_SIZE - expo));
	}
	return (out);
}

inline static void	sf_utoa64(__UINT64_TYPE__ v, char *buff, int *writen)
{
	int	i;
	static const unsigned long long	log[20] = {1ull, 10ull, 100ull, 1000ull,

	10000ull, 100000ull, 1000000ull, 10000000ull, 100000000ull, 1000000000ull,
	10000000000ull, 100000000000ull, 1000000000000ull, 10000000000000ull,
	100000000000000ull, 1000000000000000ull, 10000000000000000ull,
	100000000000000000ull, 1000000000000000000ull, 10000000000000000000ull};
	if (v == 0)
		buff[(*writen)++] = '0';
	i = 1;
	while (i < 20 && v >= log[i])
		++i;
	while (i)
		buff[(*writen)++] = '0' + (v / log[--i]) % 10;
}

//if buff == NULL, then work a generic char *dtoa(double v, int precison) and writen (if not null) is equal to strlen of buff returned

char	*ft_dtoa(__T_FLOAT f, int precision, char *buff, int *writen)
{
	t_float			v;
	__T_FLOAT_I		expo;
	__T_FLOAT_UI	mant;
	__T_FLOAT_UI	frac;
	__T_FLOAT_UI	mask; //32b
	int				w;
	int				t;

	v = (t_float){.f = f};
	if (buff == NULL)
	{
		if ((buff = malloc(
			((w = ft_float_evaluate_size(v, precision)) + 1))) == NULL)
			return (NULL);
		buff[w] = '\0'; //si buff est cree, on ajoute un '\0' a la fin (le '\0' n'est pas present par defaut)
	}
	w = 0;
	if (writen != NULL)
		*writen = 0;
	else
		writen = &w; //simule la presence de writen
	if (f != f)
	{
		buff[0] = 'n';
		buff[1] = 'a';
		buff[2] = 'n';
		*writen = 3;
		return (buff);
	}
	if (v.part.sign && !(v.part.sign == 0))
		buff[(*writen)++] = '-';
	if (v.part.exp == __INFINITY_EXP)
	{
		buff[(*writen)++] = 'i';
		buff[(*writen)++] = 'n';
		buff[(*writen)++] = 'f';
		return (buff);
	}
	mant = v.part.exp ? v.part.mant | __T_FLOAT_MANT_COMP : v.part.mant;
	expo = v.part.exp - __T_FLOAT_EXP_BIAS;
	mask = ((__T_FLOAT_UI)-1) >> (__T_FLOAT_BSIZE - __T_FLOAT_MANT_SIZE - 1); //32 - 1 - 23 = 8 = 0x00FFFFFF;
	if (v.part.exp == 0) //subnormal numbers
	{
		buff[(*writen)++] = '0';
		frac = mant & mask;
	}
	else if (expo > __T_FLOAT_EXP_BIAS || expo <= -__T_FLOAT_EXP_BIAS)
		return (NULL);
	else if (expo >= __T_FLOAT_MANT_SIZE)
		sf_utoa64(mant << (expo - __T_FLOAT_MANT_SIZE), buff, writen);
//		printf("%llu", (uint64_t)(mant << (expo - __T_FLOAT_MANT_SIZE)));
	else if (expo >= 0)
	{
		sf_utoa64(mant >> (__T_FLOAT_MANT_SIZE - expo), buff, writen);
//		printf("%llu", (uint64_t)(mant >> (__T_FLOAT_MANT_SIZE - expo)));
		frac = (mant << (expo + 1)) & mask;
	}
	else
	{
		buff[(*writen)++] = '0';
		frac = ((mant) >> -(expo + 1)) & mask; //perte de 3 bits de precision (pas sur)
		//0b00111101110011001100110011001101 = 0.1000000001
		//0b00111101110011001100110011001000 = 0.0999999996 (dtoa sort des nombres plus petits que prevus)
		//0b00000000000000000000000000000101 = diff
	}
	if (precision > 0)
	{
		buff[(*writen)++] = '.';
		frac = (frac << 3) + (frac << 1);
		while (--precision >= 0)
		{
			buff[(*writen)++] = (frac >> (__T_FLOAT_MANT_SIZE + 1)) + '0';
//			printf("%c", (int)(frac >> (__T_FLOAT_MANT_SIZE + 1)) + '0');
			frac &= mask;
			frac = (frac << 3) + (frac << 1);
		}
		//manque l'arondi
		if (frac >> (__T_FLOAT_MANT_SIZE + 1) >= 5)
		{
			t = *writen - 1;
			while (t >= 0 && (buff[t] == '9' || buff[t] == '.'))
				if (buff[t--] == '9')
					buff[t + 1] = '0';
			if (t < 0)
			{
				ft_memmove(buff + 1, buff, ++(*writen));
				buff[0] = '1';
			}
			else
				++buff[t];
		}
	}
	return (buff);
}

//0.1000000000000000055511151231257827021181583404541015625000000000
//0.100000001490116119384765625
