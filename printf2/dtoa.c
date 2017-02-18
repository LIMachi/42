/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 15:41:37 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/18 14:02:24 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include "ft_float.h"

#define MASK ((__T_FLOAT_UI)-1) >> (__T_FLOAT_BSIZE - __T_FLOAT_MANT_SIZE - 1)

void	print_all_defined()
{
	printf("__T_FLOAT_SIZE: %d\n", __T_FLOAT_SIZE);
	printf("__T_FLOAT_EXP_SIZE: %d\n", __T_FLOAT_EXP_SIZE);
	printf("__T_FLOAT_MANT_SIZE: %d\n", __T_FLOAT_MANT_SIZE);
	printf("__T_FLOAT_BSIZE: %d\n", __T_FLOAT_BSIZE);
	printf("__T_FLOAT_EXP_BIAS: %d\n", __T_FLOAT_EXP_BIAS);
	printf("__T_FLOAT_MANT_COMP: %d\n", __T_FLOAT_MANT_COMP);
	printf("__INFINITY_EXP: %d\n", __INFINITY_EXP);
	printf("INFINITY: %d\n", INFINITY);
}

void	print_binary(__T_FLOAT_UI v, int bites)
{
	while (bites--)
		printf("%d", (v >> bites) & 1);
}

char	*ft_dtoa_a(double f, int precision, char *buff)
{
	t_float	v;

	return (NULL);
}

char	*ft_ulltoa(__UINT64_TYPE__ v, char *buff)
{

}

char	*ft_dtoa(__T_FLOAT f, int precision, char *buff)
{
	t_float			v;
	__T_FLOAT_I		expo;
	__T_FLOAT_UI	mant;
	__T_FLOAT_UI	frac;

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
	if (expo > __T_FLOAT_EXP_BIAS || expo <= -__T_FLOAT_EXP_BIAS)
		return (NULL);
	else if (expo >= __T_FLOAT_MANT_SIZE)
		printf("%llu", (uint64_t)(mant << (expo - __T_FLOAT_MANT_SIZE)));
	else if (expo >= 0)
	{
		printf("%llu", (uint64_t)(mant >> (__T_FLOAT_MANT_SIZE - expo)));
		frac = (mant << (expo + 1)) & MASK;
	}
	else
	{
		printf("0");
		frac = ((mant & MASK) >> -(expo + 1));
	}
	if (precision > 0)
	{
		printf(".");
		while (!(0 * (frac *= 10)) && --precision >= 0)
		{
			printf("%c", (int)(frac >> (__T_FLOAT_MANT_SIZE + 1)) + '0');
			frac &= MASK;
		}
		//still needs rounding
	}
	return (NULL);
}

int	main(int argc, char **argv, char **env)
{
	print_all_defined();
	int	p = 17;
	t_float	t = {.f = 1.1};
	print_binary(1, 1);
	print_binary(0, __T_FLOAT_EXP_SIZE);
	print_binary((__T_FLOAT_UI)-1, __T_FLOAT_MANT_SIZE);
	printf("\n");
	print_binary(t.part.sign, 1);
	print_binary(t.part.exp, __T_FLOAT_EXP_SIZE);
	print_binary(t.part.mant, __T_FLOAT_MANT_SIZE);
	printf("\nsizeof t_float: %lu\n", sizeof(t_float));
	ft_dtoa(t.f, p, NULL);
	printf("\n%.*f\n", p, t.f);
	return (0);
}
