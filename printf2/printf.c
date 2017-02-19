/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 18:15:18 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/19 21:04:25 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//gcc -D__T_FLOAT_SIZE=8 printf.c && ./a.out && clang -D__T_FLOAT_SIZE=8 printf.c && ./a.out

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <wchar.h>

//#include <math.h>

#include "dtoa.c"

#include "ft_int.h"

//conclusion actuelles: les args somnt stocke dans des blocs de 8 octes (64 bits)

int				ft_printf(const char *format, ...)
{
	va_list		ap;

	va_start(ap, format);
	printf("%lld\n", (long long)va_arg(ap, t_int128));
	printf("%lld\n", (long long)va_arg(ap, t_int128));
	printf("%lld\n", (long long)va_arg(ap, t_int128));
	va_end(ap);
	return (0);
}

# define M_LOG10_2L		0.301029995663981195225646428359489448L

size_t	ft_length(unsigned long long v)
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

void	print_binary(__T_FLOAT_UI v, int bites)
{
	while (bites--)
		printf("%d", (int)(v >> bites) & 1);
}

int	main()
{
	t_float	test;
	test.f = 9.99999999999;
	int			p = 10;
	char		*str;
	int			t;

	//0b00111101110011001100110011001101 = 0.1000000001
	//0b00111101110011001100110011001000 = 0.0999999996
	//0b00000000000000000000000000000101 = diff
//	test.f = 0.099999964237213134765625;
//	test.ui = 0b00111101110011001100110011001100;
	printf("0bSeeeeeeeeeeeMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n0b");
	print_binary(test.ui, __T_FLOAT_BSIZE);
	printf("\n[printf]:  %.*f\n", p, test.f);
	str = ft_dtoa(test.f, p, NULL, &t);
	printf("[ft_dtoa]: %s\n", str);
	printf("t: %d\t0x%016llx\n\n", t, (__UINT64_TYPE__)test.ui);
	free(str);
	return (0);
}
