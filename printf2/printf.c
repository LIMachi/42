/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 18:15:18 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/22 19:34:29 by lee              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//gcc -D__T_FLOAT_SIZE=8 printf.c && ./a.out && clang -D__T_FLOAT_SIZE=8 printf.c && ./a.out
//gcc -D__T_FLOAT_SIZE=8 -I../libft/inc printf.c ../libft/libft.a && ./a.out

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <wchar.h>

//#include <math.h>

#include "dtoa.c"

#include "ft_int.h"

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
	__uint128_t		ui;
	__T_FLOAT		f;
	void			*p;
}				t_printf_arg;

typedef struct	s_printf_form
{
	int				attr;
	int				ind_field;
	int				ind_precision;
	int				field;
	int				precision;
	int				tlength;
	int				type;
	t_printf_arg	arg;
}				t_printf_form;

t_printf_form	*sf_prepare_forms(const char *format)
{
	int				count;
	int				i;
	t_printf_form	*out;

	count = 0;
	i = -1;
	while (format[++i] != '\0' && format[i + 1] != '\0')
		if (format[i] == '%' && format[++i] != '%')
			++count;
	if ((out = ft_memalloc(sizeof(t_printf_form) * (count + 1))) == NULL)
		return (NULL);
	out[count].arg.ui = -1;
	return (out);
}

int	ft_strcchr(const char *str, int c)
{
	int	out;

	out = 0;
	while (str[out] != '\0' && str[out] != c)
		++out;
	return (str[out] == '\0' ? -1 : out);
}

int	parse_number(const char *format, int *number, int *arg_number, int *pos)
{
	int	tmp;

	if (format[*pos] == '*')
	{
		if (ft_strcchr("123456789", format[++(*pos)]) != -1)
		{
			*number = 0;
			tmp = *pos;
			while (format[tmp] != '\0' && ft_isdigit(format[tmp]))
				*number = (*number) * 10 + format[tmp++] - '0';
			(format[tmp] == '$') ? (*pos = tmp + 1) :
								(*number = (*arg_number)++);
		}
		else
			*number = (*arg_number)++;
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

/*
t_printf_form	sf_parse_attributes(char *format, int *pos, int *arg_number)
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
		else if (format[*pos] == '.')
		{
			if (tmp = parse_number(format, &out.precision, arg_number, &((*pos)++)) == -1)
				out.precision = -1;
			else
				out.ind_precision = tmp;
		}
		else if (format[*pos] == '*' || (format[*pos] >= '1' && format[*pos] <= '9'))
			out.ind_field = parse_number(format, &out.field, arg_number, pos) == -1)
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
*/

/*	shift
%	-1(0)	% symbol
d	0		signed
i	1		signed
o	2		octal unsigned
u	3		unsigned
x	4		hexa unsigned
e	5		exponent float
f	6		standard float
g	7		auto float (standard or exponent)
a	8		hexa float
c	9		char or wchar_t (if l present)
s	10		string (of wchar_t if l present)
p	11		void ptr printed as %#x
n	12		store nb of characters printed in ptr
m	13		print strerror(errno)
b	14		print binary
*/

/*	shift
h	0		short
l	1		long
L	2		long double
j	3		intmax_t
z	4		ssize_t
t	5		ptrdiff_t
M	6		__int128_t
hh	7		char
ll	8		long long
*/

int	sf_parse_attributes_0(const char *format, int *pos, int *arg_number,
						t_printf_form *out)
{
	int				tmp;

	while (ft_strcchr("%dDioOuUxXeEfFgGaAcCsSpnmbB", format[*pos]) == -1)
	{
		if ((tmp = ft_strcchr("#0- +'I", format[*pos])) != -1 && ++(*pos))
		{
			out->attr |= 1 << tmp;
			out->attr & 4 ? out->attr &= ~2 : 0;
			out->attr & 16 ? out->attr &= ~8 : 0;
		}
		else if (format[*pos] == '.' && ++(*pos) && !(0 & (out->attr &= ~2)))
			(tmp = parse_number(format, &out->precision, arg_number,
				pos) == -1) ? (out->precision = -1) :
				(out->ind_precision = tmp);
		else if (format[*pos] == '*' ||
				(format[*pos] >= '1' && format[*pos] <= '9'))
			out->ind_field = parse_number(format, &out->field, arg_number, pos);
		else if ((tmp = ft_strcchr("hlLjztM", format[*pos])) != -1 && ++(*pos))
			out->tlength = 1 << (tmp + 7 * (((tmp == 0 && format[*pos] == 'h')
					|| (tmp == 1 && format[*pos] == 'l')) && !(0 & ++(*pos))));
		else
			return (-1);
	}
	return (0);
}

int	sf_parse_attributes(const char *format, int *pos, int *arg_number,
						t_printf_form *form)
{
	int		tmp;
	int		out;

	form->arg.ui = -1;
	if (format[*pos] >= '1' && format[*pos] <= '9')
	{
		tmp = *pos;
		form->arg.ui = 0;
		while (format[tmp] != '\0' && ft_isdigit(format[tmp]))
			form->arg.ui = (form->arg.ui) * 10 + format[tmp++] - '0';
		--form->arg.ui;
		if (format[tmp] != '$')
			form->arg.ui = -1;
		else
			*pos = tmp + 1;
	}
	if (sf_parse_attributes_0(format, pos, arg_number, form))
		return (-1);
	if ((tmp = ft_strcchr("%diouxefgacspnmL", format[*pos])) != -1)
		form->type = 1 << (tmp - 1);
	else
	{
		form->tlength = 2;
		form->type = 1 << (ft_strcchr(" D OUXEFGACS", format[*pos]) - 1);
	}
//	printf("\n*arg_number: %d\n",*arg_number);
//	printf("arg.ui: %lld\n", (long long)form->arg.ui);
	form->arg.ui == -1 ? form->arg.ui = (*arg_number)++ : 0;
//	printf("arg.ui: %lld\n", (long long)form->arg.ui);
	out = *arg_number >= form->arg.ui ? *arg_number : form->arg.ui;
	form->ind_precision && out < form->precision ? out = form->precision : 0;
	return (1 + (form->ind_field && out < form->field ? form->field : out));
}

void	debug_printf_forms(t_printf_form *forms)
{
	int	i;

	printf("\ndebug:");
	i = -1;
	while (forms[++i].arg.ui != -1)
	{
		printf("\nattrinutes: "); print_binary(forms[i].attr, 8);
		printf("\nind_field: "); print_binary(forms[i].ind_field, 1);
		printf("\nind_precision: "); print_binary(forms[i].ind_precision, 1);
		printf("\nfield: %d", forms[i].field);
		printf("\nprecision: %d", forms[i].precision);
		printf("\ntlength: "); print_binary(forms[i].tlength, 16);
		printf("\ntype: "); print_binary(forms[i].type, 16);
		printf("\nargn: %lld\n", (long long)forms[i].arg.ui);
	}
}

t_printf_form	*sf_parse_forms(const char *format, va_list _ap, int *argn)
{
	va_list			ap;
	t_printf_form	*out;
	int				i;
	int				j;
	int				tmp;
	int				argc;

	va_copy(ap, _ap);
	if ((out = sf_prepare_forms(format)) == NULL)
		return (NULL);
	i = -1;
	argc = 0;
	j = 0;
	while (format[++i] != '\0')
	{
		if (format[i] == '%' && format[++i] != '%')
		{
			if ((tmp = sf_parse_attributes(format, &i, argn,
				out + j++)) == -1)
			{
				ft_free(out);
				return (NULL);
			}
			argc < tmp ? argc = tmp : 0;
		}
	}
//	printf("args: %d\n", argc);
	*argn = argc;
	va_end(ap);
//	debug_printf_forms(out);
	return (out);
}

void	sf_form_add_arg(t_printf_form *form, t_printf_arg *args)
{
	if (form->ind_field)
		form->field = args[form->field].ui;
	if (form->ind_precision)
		form->precision = args[form->precision].ui;
	form->arg = args[form->arg.ui];
}

int		sf_parse_args(t_printf_form *forms, va_list _ap, int argn)
{
	va_list			ap;
	t_printf_arg	*args;
	int				tmp;
	int				i;

	if ((args = ft_memalloc(sizeof(t_printf_arg) * argn)) == NULL)
	{
		ft_free(forms);
		return (-1);
	}
	va_copy(ap, _ap);
	i = -1;
	while (forms[++i].arg.ui != -1)	//premier passage, on stocke uniquement la taille des arg
		args[forms[i].arg.ui].ui = forms[i].tlength & (1 << 6);
	i = -1;
	while (++i < argn)	//on remplit
		(args[i].ui) ? (args[i].ui = va_arg(ap, __uint128_t)) :
						(args[i].ui = va_arg(ap, __UINT64_TYPE__));
	i = -1;
	while(forms[++i].arg.ui != -1)
		sf_form_add_arg(forms + i, args);
	ft_free(args);
	return (0);
}

int			sf_putn_u128_fd(__uint128_t v, int fd, size_t n)
{
	static const char	tab[] = "0123456789";

	if (n == 0)
		return (0);
	if (v == 0)
		return (0);
	return (sf_putn_u128_fd(v / 10, fd, n - 1) + write(fd, &tab[v % 10], 1));
}

int			putn_u128_fd(__uint128_t v, int fd, size_t n)
{
	if (n == 0)
		return (0);
	if (v == 0)
		return (write(fd, "0", 1));
	return (sf_putn_u128_fd(v, fd, n));
}

int			putn_i128_fd(__int128_t v, int fd, size_t n)
{
	if (n == 0)
		return (0);
	if (v == 0)
		return (write(fd, "0", 1));
	if (v < -1)
		return (write(fd, "-", 1) + sf_putn_u128_fd(-v, fd, n - 1));
	return (sf_putn_u128_fd(v, fd, n));
}

typedef struct	s_printf_put_arg
{
	t_printf_form	*forms;
	size_t			size;
	const char		*format;
	size_t			pos;
}				t_printf_put_arg;

int			sf_dn_put_arg(t_printf_put_arg *parg, int formn, size_t len, int fd)
{
	size_t			limit;
	t_printf_form	form;

	limit = parg->size - len;
	form = parg->forms[formn];
	if (form.type & 1)
		while (parg->format[parg->pos] != '\0' && parg->format[parg->pos] != 'd')
			++parg->pos;
	if (form.type & 3)
		return (
			//printf("%lld", (long long)form.arg.ui)
			putn_i128_fd(form.arg.ui, fd, limit)
	);
	return (0);
}

int	ft_vdnprintf(int fd, size_t size, const char *format, va_list ap)	//en theorie, tout le parsing est fini, il ne manque que l'affichage
{
	size_t				len;
	int					tmp;
	t_printf_put_arg	parg;
	int					formn;

	len = 0;
	formn = 0;
	parg = (t_printf_put_arg){.forms = NULL, .size = size, .format = format,
							.pos = -1};
	while (len < size && format[++parg.pos] != '\0')
		if (format[parg.pos] == '%' && format[++parg.pos] != '%')
		{
			if (!(parg.forms == NULL && !(tmp = 0) && !((parg.forms =
					sf_parse_forms(format + parg.pos - 1, ap, &tmp)) == NULL ||
					sf_parse_args(parg.forms, ap, tmp))))
				return (-1);
			len += sf_dn_put_arg(&parg, formn++, len, fd);
		}
		else
			len += write(fd, format + parg.pos, 1);
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

typedef union	u_128
{
	t_int128		i128;
	__INT64_TYPE__	i64[2];
}				t_128;

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

	t_int128 test0 = 0;
	t_128 test1 = {.i64[0] = 456, .i64[1] = 789};
	t_int128 test2 = 0;

	ft_printf("test%3$Md\n", test0, test1, test2);

	return (0);
}
