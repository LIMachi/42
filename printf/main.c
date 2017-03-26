/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 18:49:10 by hmartzol          #+#    #+#             */
/*   Updated: 2017/03/23 11:09:44 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <stdio.h>
#include <ft_int.h>
#include <strings.h>
#include <string.h>

char	*thousands_sep(void)
{
	return (localeconv()->thousands_sep);
}

int	test_dtoa(void)
{
	t_float	f = {.ui = 0};
	char	buff0[1024] = {0};
	char	buff1[1024] = {0};
	int		ignore_subnormals = 1;
	int		ignore_nan = 1;
	int		ignore_inf = 1;

//	f.part.exp = 1000;
	for (f.f = 1e-10; f.f < 1; f.f += 1e-10)
	{
		if (ignore_nan && (double)f.f != (double)f.f)
			continue ;
		snprintf(buff0, 1024, "%.32f", f.f);
		ft_dtoa(f.f, 32, buff1, NULL);
		if (strcmp(buff0, buff1) && strcmp(buff1, "nan"))
			printf("printf: |%s| ft_printf: |%s|\n", buff0, buff1);
		bzero(buff0, 1024);
		bzero(buff1, 1024);
	}
	return (0);
}

void	test(int debug, ...)
{
	va_list		ap;
	float		t;

	(void)debug;
	va_start(ap, debug);
	t = va_arg(ap, double);
	printf("%f", t);
	va_end(ap);
}

int	main(void)
{
//	test(0, 14.1f);
	// return (test_dtoa());
//	t_float	f = {.part = {.sign = 0, .exp = 1023, .mant = 42425789}};
//	int		i;
//	printf("|%n|\n", &i);
//	printf("%d\n", i);
//	ft_printf("123456789%n|\n", &i);
//	printf("%d\n", i);
	ft_printf("%d\n", 85+171);
//	printf("%8p\n", NULL);
	// uint64_t	mant;
	// mant = (1ll << __T_FLOAT_MANT_SIZE) | f.part.mant;
	// printf("%s%#llx.%.*llxp%+d\n",
	// 	f.part.sign ? "-" : "",
	// 	mant >> __T_FLOAT_MANT_SIZE,
	// 	__T_FLOAT_MANT_SIZE >> 2,
	// 	mant & (((uint64_t)-1) >> (64 - __T_FLOAT_MANT_SIZE)),
	// 	f.part.exp - 1023);
//	printf("   printf: |%.120f|\n", f.f);
//	printf("ft_printf: |%s|\n", ft_dtoa(f.f, 120, NULL, NULL));
	// ft_printf("bits: %.64llb\n", f.ui);
//	f.f = 1e-10;
//	printf("   printf: |%.120f|\n", f.f);
//	printf("ft_printf: |%s|\n", ft_dtoa(f.f, 120, NULL, NULL));
	// ft_printf("bits: %.64llb\n", f.ui);
	// printf("%a\n", 12.25);
}
// 0.000000000000001000000000000000077705399876661079238307185601195015145492561714490875601768493652343750000000000000000000
// 0.000000000000000999200722162640886381268501281738281250000000000000000000000000000000000000000000000000000000000000000000
// 0.000000000100000000000000003643219731549774157916554706559963960899040102958679199218750000000000000000000000000000000000
// 0.000000000099999897251734637393383309245109558105468750000000000000000000000000000000000000000000000000000000000000000000
