/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 18:49:10 by hmartzol          #+#    #+#             */
/*   Updated: 2017/03/17 06:46:17 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <stdio.h>
#include <ft_int.h>

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__

__int128_t	pow10_i128(unsigned p)
{
 	return (p > 38 ? ((__int128_t)-1) : ((t_i128[39]){{{1, 0}}, {{10,
	0}}, {{100, 0}}, {{1000, 0}}, {{10000, 0}}, {{100000, 0}}, {{1000000, 0}},
	{{10000000, 0}}, {{100000000, 0}}, {{1000000000, 0}}, {{10000000000, 0}},
	{{100000000000, 0}}, {{1000000000000, 0}}, {{10000000000000, 0}},
	{{100000000000000, 0}}, {{1000000000000000, 0}}, {{10000000000000000, 0}},
	{{100000000000000000, 0}}, {{1000000000000000000, 0}},
	{{10000000000000000000u, 0}}, {{0x6bc75e2d63100000, 5}},
	{{0x35c9adc5dea00000, 0x36}}, {{0x19e0c9bab2400000, 0x21e}},
	{{0x2c7e14af6800000, 0x152d}}, {{0x1bcecceda1000000, 0xd3c2}},
	{{0x161401484a000000, 0x84595}}, {{0xdcc80cd2e4000000, 0x52b7d2}},
	{{0x9fd0803ce8000000, 0x33b2e3c}}, {{0x3e25026110000000, 0x204fce5e}},
	{{0x6d7217caa0000000, 0x1431e0fae}}, {{0x4674edea40000000, 0xc9f2c9cd0}},
	{{0xc0914b2680000000, 0x7e37be2022}}, {{0x85acef8100000000, 0x4ee2d6d415b}},
	{{0x38c15b0a00000000, 0x314dc6448d93}}, {{0x378d8e6400000000,
	0x1ed09bead87c0}},	{{0x2b878fe800000000, 0x13426172c74d82}},
	{{0xb34b9f1000000000, 0xc097ce7bc90715}}, {{0xf436a000000000,
	0x785ee10d5da46d9}}, {{0x98a224000000000, 0x4b3b4ca85a86c47a}}}[p].i128));
}

#else

# if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__

__int128_t	pow10_i128(unsigned p)
{
 	return (p > 38 ? ((__int128_t)-1) : ((t_i128[39]){{{0, 1}}, {{0,
	10}}, {{0, 100}}, {{0, 1000}}, {{0, 10000}}, {{0, 100000}}, {{0, 1000000}},
	{{0, 10000000}}, {{0, 100000000}}, {{0, 1000000000}}, {{0, 10000000000}},
	{{0, 100000000000}}, {{0, 1000000000000}}, {{0, 10000000000000}},
	{{0, 100000000000000}}, {{0, 1000000000000000}}, {{0, 10000000000000000}},
	{{0, 100000000000000000}}, {{0, 1000000000000000000}},
	{{0, 10000000000000000000u}}, {{5, 0x6bc75e2d63100000}},
	{{0x36, 0x35c9adc5dea00000}}, {{0x21e, 0x19e0c9bab2400000}},
	{{0x152d, 0x2c7e14af6800000}}, {{0xd3c2, 0x1bcecceda1000000}},
	{{0x84595, 0x161401484a000000}}, {{0x52b7d2, 0xdcc80cd2e4000000}},
	{{0x33b2e3c, 0x9fd0803ce8000000}}, {{0x204fce5e, 0x3e25026110000000}},
	{{0x1431e0fae, 0x6d7217caa0000000}}, {{0xc9f2c9cd0, 0x4674edea40000000}},
	{{0x7e37be2022, 0xc0914b2680000000}}, {{0x4ee2d6d415b, 0x85acef8100000000}},
	{{0x314dc6448d93, 0x38c15b0a00000000}}, {{0x1ed09bead87c0,
	0x378d8e6400000000}}, {{0x13426172c74d82, 0x2b878fe800000000}},
	{{0xc097ce7bc90715, 0xb34b9f1000000000}}, {{0x785ee10d5da46d9,
	0xf436a000000000}}, {{0x4b3b4ca85a86c47a, 0x98a224000000000}}}[p].i128));
}

# else

#  error "Invalid endian"

# endif

#endif

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

char	*thousands_sep(void)
{
	return (localeconv()->thousands_sep);
}

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
//	char test[] = "|%#b|\n";
//	printf("%s", test);
//	ft_printf(test, 1);
//	setlocale(LC_NUMERIC, "");
//	printf("|%s|\n", thousands_sep());
//	int	truc = 262648092;
//	printf("   printf: |% #'20.10u|\n", -truc); // |+262648092         |
//	ft_printf("ft_printf: |% #'20.10u|\n", -truc);
	// __int128_t i[40];
	// int j;
	// int n;
	// for (int _ = 0; _ < 40; ++ _)
	// 	i[_] = pow10_i128(_);
	// j = ft_printf("%1$3v*2$hh#x\n", "ceci est un gros troll :p", 26);
	// printf("%d\n", j);
	__int128_t t = -1;
	ft_printf("%hhb\n", -42);
//	printf("|%-0#10.5hhx|\n", &t);
	return (0);
}
