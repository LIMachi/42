/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 18:49:10 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/28 09:19:09 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <stdio.h>

//conclusion actuelles: les args somnt stocke dans des blocs de 8 octes (64 bits)

/*
int				ft_printf(const char *format, ...)
{
	va_list		ap;

	va_start(ap, format);
	printf("int size: %d\n", sizeof(int));
	printf("%lld\n", (long long)va_arg(ap, int));
	printf("%lld\n", (long long)va_arg(ap, int));
	printf("%lld\n", (long long)va_arg(ap, int));
	va_end(ap);
	return (0);
}
*/

int	main()
{
//	t_float	test;
//	test.f = 9.99999999999;
//	int			p = 10;
//	char		*str;
//	int			t;

	//0b00111101110011001100110011001101 = 0.1000000001
	//0b00111101110011001100110011001000 = 0.0999999996
	//0b00000000000000000000000000000101 = diff
//	test.f = 0.099999964237213134765625;
//	test.ui = 0b00111101110011001100110011001100;
//	printf("0bSeeeeeeeeeeeMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n0b");
//	print_binary(test.ui, __T_FLOAT_BSIZE);
//	printf("\n[printf]:  %.*f\n", p, /*test.f*/42.25);
//	str = ft_dtoa(test.f, p, NULL, &t);
//	printf("[ft_dtoa]: %s\n", str);
//	printf("t: %d\t0x%016llx\n\n", t, (__UINT64_TYPE__)test.ui);
//	free(str);
//	ft_printf("test\n");

//	170141183460469231731687303715884105727

//	t_i128 test1 = {.u64[0] = 0xFFFFFFFFFFFFFFFF, .u64[1] = 0xFFFFFFFFFFFFFFFF
					//.i64[0] = 0x0000000f00000000, .i64[1] = 0x8000000000000000
//				};
//	t_int128 test2 = 42;
//	t_int128 test0 = -3;
//	long	test3;
//	test3 = 0x8000000000000000;
//	test3 = 0x7FFFFFFFFFFFFFFF;
//	test3 = -57;
//	int	test3 = -57;

//	ft_printf("ft_printf: \ntest1: %2$Md\ntest2: %3$Md\ntest0: %1$Md\ntestd0: %Md\ntestd1: %d\ntestd2: %d\ntestd3: %d\n", test0, test1, test2, test3);
//	int	_test1 = -1;
//	int	_test2 = 42;
//	int	_test0 = -3;
//	int	_test3 = -57;
//	printf("\nprintf: \ntest1: %2$d\ntest2: %3$d\ntest0: %1$d\ntestd0: %d\ntestd1: %d\ntestd2: %d\ntestd3: %d\n", _test0, _test1, _test2, _test3);
	//printf utilise une alloc de moins que ft_printf dans ce test, mais le mien s'explique par la gestion des arguments int128 et sans doute bientot long double
	//mon parcours est lineaire, la ou printf (pour les sources que j'ai vu) est particulier (pour ne pas dire bordelique pour les $)
	//ft_printf("%ld\n", test3);
//	t_i128	t = {.u64[1] = 0xF000000000000000, .u64[0] = 0};
//	printf("%llx\n", t.u128);
//	ft_printf("%Mx\n", t.u128);
//	printf("%#o\n", 1);
	char test[] = "|%#b|\n";
	printf("%s", test);
	ft_printf(test, 1);
	setlocale(LC_NUMERIC, "");
	printf("|%s|\n", thousands_sep());
	int	truc = 262648092;
	printf("|%+-20.15d|\n", truc); // |+262648092         |
	ft_printf("|%+-20.15d|\n", truc);
	return (0);
}
