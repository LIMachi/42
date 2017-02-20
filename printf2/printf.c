/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 18:15:18 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/20 17:21:07 by hmartzol         ###   ########.fr       */
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

/*
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
*/

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

//printf("%12.12f", 42.0);
//printf("%2$*1$.*1$f", 12, 42.0);

char idee[] =
"parsing de $: "
"chercher toutes les instances de % seul "
"faire une table d'arg "
"chercher dans les % les instances de $ et verifier la validité "
"stocker les plus grand $ trouvé (éventuellement gerer le 128bits?) "
"allouer un tableau de union_type pour stocker les args "
"remplir tout le tableau avec les arg (reparser pour les 128bits?) "
"lancer printf";

typedef union	u_printf_arg
{
	__uint128_t	ui;
	__T_FLOAT	f;
	void		*p;
}				t_printf_arg;

typedef struct	s_printf_form
{
	int				attr;
	int				dolar_field : 1;
	int				dolar_precision : 1;
	int				dolar_content : 1;
	int				padding : (__SIZEOF_INT__ * 8 - 3);
	int				field;
	int				precision;
	int				tlength;
	int				type;
	t_printf_arg	arg;
}				t_printf_form;

t_printf_form	*sf_prepare_forms(const char *format)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (format[++i] != '\0')
		if (format[i] == '%' && format[i + 1] != '%')
			++count;
	return (malloc(sizeof(t_printf_form) * count));
}

int	ft_strcchr(const char *str, int c)
{
	int	out;

	out = 0;
	while (str[out] != '\0' && str[out] != c)
		++out;
	return (str[out] == '\0' ? -1 : out);
}

int	parse_number(char *format, int *number, int arg_number, int *pos)
{
	int	tmp;

	if (format[*pos] == '*')
	{
		*number = arg_number;
		if (ft_strcchr("123456789", format[++(*pos)]) != -1)
		{
			*number = arg_number;
			tmp = *pos;
			while (format[tmp] != '\0' && ft_isdigit(format[tmp]))
				*number = (*number) * 10 + format[tmp++] - '0';
			if (format[tmp] == '$')
				*pos = tmp + 1;
			else
				*number = arg_number;
		}
		return (1);
	}
	if (format[*pos] >= '1' && format[*pos] <= '9')
	{
		while (format[*pos] != '\0' && ft_isdigit(format[*pos]))
			*number = (*number) * 10 + format[(*pos)++] - '0';
		return (0);
	}
	return (-1);
}

t_printf_form	sf_parse_attributes(char *format, int *pos)
{
	t_printf_form	out;
	int				tmp;

	tmp = -1;
	out = (t_printf_form){0};
	while (ft_strcchr("%dDioOuUxXeEfFgGaAcCsSpnm", format[*pos]) == -1)
	{
		if ((tmp = ft_strcchr("#0- +'I", format[*pos])) != -1)
		{
			out.attr |= 1 << tmp;
			out.attr & 4 ? out.attr &= ~2 : 0;
			out.attr & 16 ? out.attr &= ~8 : 0;
		}
		else if ('.')
		{

		}
		else if ('*')
		{

		}
		else if (ft_isdigit(format[*pos]))
		{

		}
		else
			return ((t_printf_form){0});
		++(*pos);
	}
	if (format[*pos] == '\0')
		out.type = 0;
	else
	{
		if ((out.type = ft_strcchr("%diouxefgacspnm", format[*pos])) != -1)
			out.type = 1 << out.type;
		else
			out.type = 1 << ft_strcchr(" D OUXEFGACS", format[*pos]);
	}
}

t_printf_form	*sf_parse_forms(const char *format, va_list _ap)
{
	va_list			ap;
	t_printf_form	*out;
	int				i;
	int				f;

	va_copy(ap, _ap);
	if ((out = sf_prepare_forms(format)) == NULL)
		return (NULL);
	i = -1;
	f = 0;
	while (format[++i] != '0')
		if (format[i] == '%' && format[++i] != '%')
			out[f++] = sf_parse_attributes((char*)format, &i);
	va_end(ap);
	return (out);
}

t_printf_arg	*sf_parse_args(t_printf_form *forms, va_list _ap)
{
	va_list	ap;

	va_copy(ap, _ap);
	(void)forms;
	(void)ap;
	return (NULL);
}

int				sf_dn_put_arg(size_t argn, t_printf_form *forms,
								t_printf_arg *args, size_t *pos)
{
	(void)argn;
	(void)forms;
	(void)args;
	(void)pos;
	return (0);
}

int	ft_vdnprintf(int fd, size_t size, const char *format, va_list ap)
{
	t_printf_arg	*args;
	t_printf_form	*forms;
	size_t			pos;
	size_t			len;
	size_t			argn;

	forms = NULL;
	args = NULL;
	pos = -1;
	len = 0;
	argn = 0;
	while (len < size && format[++pos] != '\0')
		if (format[pos] == '%' && format[pos++] != '%')
		{
			if (forms == NULL && args == NULL &&
					!((forms = sf_parse_forms(format + pos, ap)) == NULL ||
					(args = sf_parse_args(forms + pos, ap)) == NULL))
				return (-1);
			else
				len += sf_dn_put_arg(++argn, forms, args, &pos);
		}
		else
			len += write(fd, format + pos, 1);
	return (len);
}

int	ft_printf(const char *format, ...)
{
	int		out;
	va_list	ap;

	va_start(ap, format);
	out = ft_vdnprintf(1, -1ul, format, ap);
	va_end(ap);
	return (out);
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
//	printf("0bSeeeeeeeeeeeMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n0b");
//	print_binary(test.ui, __T_FLOAT_BSIZE);
//	printf("\n[printf]:  %.*f\n", p, /*test.f*/42.25);
	str = ft_dtoa(test.f, p, NULL, &t);
	str[strlen(str)] = 'g';
	printf("[ft_dtoa]: %s\n", str);
//	printf("t: %d\t0x%016llx\n\n", t, (__UINT64_TYPE__)test.ui);
	free(str);
//	ft_printf("test\n");
	return (0);
}
