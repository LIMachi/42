/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 18:15:18 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/23 17:05:52 by lee              ###   ########.fr       */
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
	__int128_t		i;
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

#define PT_PERCENT	0
#define PT_D		1
#define PT_I		2
#define PT_O		4
#define PT_U		8
#define PT_X		16
#define PT_E		32
#define PT_F		64
#define PT_G		128
#define PT_A		256
#define PT_C		512
#define PT_S		1024
#define PT_P		2048
#define PT_N		4096
#define PT_M		8192
#define PT_B		16384

#define PTL_INT		0
#define PTL_SHORT	1
#define PTL_LONG	2
#define PTL_LONGD	4
#define PTL_INTMAX	8
#define PTL_SSIZE	16
#define PTL_PTRDIFF	32
#define PTL_INT128	64
#define PTL_CHAR	128
#define PTL_LONGL	256

#define PA_HASH		1
#define PA_ZERO		2
#define PA_MINUS	4
#define PA_SPACE	8
#define PA_PLUS		16
#define PA_AQ		32
#define PA_I		64
#define PA_MAJ		128

int	sf_parse_attributes_0(const char *format, int *pos, int *arg_number,
						t_printf_form *out)
{
	int				tmp;

	out->tlength = 0;
	while (ft_strcchr("%dDioOuUxXeEfFgGaAcCsSpnmbB", format[*pos]) == -1)
	{
		if ((tmp = ft_strcchr("#0- +'I", format[*pos])) != -1 && ++(*pos))
		{
			out->attr |= 1 << tmp;
			out->attr & PA_MINUS ? out->attr &= ~PA_ZERO : 0;
			out->attr & PA_PLUS ? out->attr &= ~PA_SPACE : 0;
		}
		else if (format[*pos] == '.' && !(0 & (out->attr &= ~PA_ZERO)))
			++(*pos) && (tmp = parse_number(format, &out->precision, arg_number,
				pos) == -1) ? (out->precision = -1) :
							(out->ind_precision = tmp);
		else if (format[*pos] == '*' ||
				(format[*pos] >= '1' && format[*pos] <= '9'))
			out->ind_field = parse_number(format, &out->field, arg_number, pos);
		else if ((tmp = ft_strcchr("hlLjztM", format[*pos])) != -1 && ++(*pos))
			out->tlength |= 1 << (tmp + 7 * (((tmp == 0 && format[*pos] == 'h')
					|| (tmp == 1 && format[*pos] == 'l')) && !(0 & ++(*pos))));
		else
			return (-1);
	}
	return (0);
}

int	sf_validate_form(t_printf_form *form)
{
	(void)form;
	return (1);
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
	if ((tmp = ft_strcchr("%diouxefgacspnm", format[*pos])) != -1)
		form->type = 1 << (tmp - 1);
	else if (ft_strcchr("DUXEFGACS", format[*pos]) != -1)
	{
		(ft_strcchr("DUCS", format[*pos]) != -1) ? (form->tlength |= PTL_LONG) :
												(form->attr |= PA_MAJ);
		form->type = 1 << (ft_strcchr(" D  UXEFGACS", format[*pos]) - 1);
	}
	else
		return (-1);
	form->arg.ui == (__uint128_t)-1 ? form->arg.ui = (*arg_number)++ : 0;
	if (!sf_validate_form(form))
		return (-1);
	out = *arg_number >= (int)form->arg.ui ? *arg_number : (int)form->arg.ui;
	form->ind_precision && out < form->precision ? out = form->precision : 0;
	return (1 + (form->ind_field && out < form->field ? form->field : out));
}

void	debug_printf_forms(t_printf_form *forms)
{
	int	i;

	printf("\ndebug:");
	i = -1;
	while (forms[++i].arg.ui != (__uint128_t)-1)
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
//	int				tmp;
	int				i;

	if ((args = ft_memalloc(sizeof(t_printf_arg) * argn)) == NULL)
	{
		ft_free(forms);
		return (-1);
	}
	va_copy(ap, _ap);
	i = -1;
	while (forms[++i].arg.ui != (__uint128_t)-1)	//premier passage, on stocke uniquement la taille des arg
		args[forms[i].arg.ui].ui |= forms[i].tlength & PTL_INT128;
	i = -1;
	while (++i < argn)	//on remplit
		(args[i].ui) ? (args[i].ui = va_arg(ap, __uint128_t)) :
						(args[i].ui = va_arg(ap, __UINT64_TYPE__));
	i = -1;
	while(forms[++i].arg.ui != (__uint128_t)-1)
		sf_form_add_arg(forms + i, args);
	ft_free(args);
	return (0);
}

int			sf_putn_x128_fd(__uint128_t v, int fd, size_t n, int maj)
{
	static const char	tab[] = "0123456789abcdef";
	static const char	tabm[] = "0123456789ABCDEF";

	if (n == 0)
		return (0);
	if (v == 0)
		return (0);
	if (maj)
		return (sf_putn_x128_fd(v / 16, fd, n - 1, maj)
				+ write(fd, &tabm[v % 16], 1));
	return (sf_putn_x128_fd(v / 16, fd, n - 1, maj)
			+ write(fd, &tab[v % 16], 1));
}

int			putn_x128_fd(__uint128_t v, int fd, size_t n, int maj)
{
	if (n == 0)
		return (0);
	if (v == 0)
		return (write(fd, "0", 1));
	return (sf_putn_x128_fd(v, fd, n, maj));
}

int			putn_xlong_fd(long v, int fd, size_t n, int maj)
{
	if (n == 0)
		return (0);
	if (v == 0)
		return (write(fd, "0", 1));
	return (sf_putn_x128_fd(v, fd, n, maj));
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
	if (v & (__int128_t)1 << (__SIZEOF_INT128__ * 8 - 1))
		return (write(fd, "-", 1) + sf_putn_u128_fd(-v, fd, n - 1));
	return (sf_putn_u128_fd(v, fd, n));
}

int			putn_llong_fd(long long v, int fd, size_t n)
{
	if (n == 0)
		return (0);
	if (v == 0)
		return (write(fd, "0", 1));
	if (v & 1ll << (__SIZEOF_LONG_LONG__ * 8 - 1))
		return (write(fd, "-", 1) + sf_putn_u128_fd(-(__int128_t)v, fd, n - 1));
	return (sf_putn_u128_fd(v, fd, n));
}

int			putn_long_fd(long v, int fd, size_t n)
{
	if (n == 0)
		return (0);
	if (v == 0)
		return (write(fd, "0", 1));
	if (v & 1l << (__SIZEOF_LONG__ * 8 - 1))
		return (write(fd, "-", 1) + sf_putn_u128_fd(-(__int128_t)v, fd, n - 1));
	return (sf_putn_u128_fd(v, fd, n));
}

int			putn_int_fd(int v, int fd, size_t n)
{
	if (n == 0)
		return (0);
	if (v == 0)
		return (write(fd, "0", 1));
	if (v & 1 << (__SIZEOF_INT__ * 8 - 1))
		return (write(fd, "-", 1) + sf_putn_u128_fd(-(__int128_t)v, fd, n - 1));
	return (sf_putn_u128_fd(v, fd, n));
}

int			putn_short_fd(short v, int fd, size_t n)
{
	if (n == 0)
		return (0);
	if (v == 0)
		return (write(fd, "0", 1));
	if (v & 1 << (__SIZEOF_SHORT__ * 8 - 1))
		return (write(fd, "-", 1) + sf_putn_u128_fd(-(__int128_t)v, fd, n - 1));
	return (sf_putn_u128_fd(v, fd, n));
}

int			putn_char_fd(char v, int fd, size_t n)
{
	if (n == 0)
		return (0);
	if (v == 0)
		return (write(fd, "0", 1));
	if (v & 1 << 7)
		return (write(fd, "-", 1) + sf_putn_u128_fd(-(__int128_t)v, fd, n - 1));
	return (sf_putn_u128_fd(v, fd, n));
}

typedef struct	s_printf_put_arg
{
	t_printf_form	*forms;
	size_t			size;
	const char		*format;
	size_t			pos;
}				t_printf_put_arg;

int			sf_jump_form(int type, const char *format, size_t *pos)
{
	char			*ec;

	ec = NULL;
	type == PT_PERCENT ? ec = (char[2]){'%', '\0'} : 0;
	type == PT_D ? ec = (char[2]){'d', 'D'} : 0;
	type == PT_I ? ec = (char[2]){'i', '\0'} : 0;
	type == PT_O ? ec = (char[2]){'o', '\0'} : 0;
	type == PT_U ? ec = (char[2]){'u', 'U'} : 0;
	type == PT_X ? ec = (char[2]){'x', 'X'} : 0;
	type == PT_E ? ec = (char[2]){'e', 'E'} : 0;
	type == PT_F ? ec = (char[2]){'f', 'F'} : 0;
	type == PT_G ? ec = (char[2]){'g', 'G'} : 0;
	type == PT_A ? ec = (char[2]){'a', 'A'} : 0;
	type == PT_C ? ec = (char[2]){'c', 'C'} : 0;
	type == PT_S ? ec = (char[2]){'s', 'S'} : 0;
	type == PT_P ? ec = (char[2]){'p', '\0'} : 0;
	type == PT_N ? ec = (char[2]){'n', '\0'} : 0;
	type == PT_M ? ec = (char[2]){'m', '\0'} : 0;
	type == PT_B ? ec = (char[2]){'b', '\0'} : 0;
	if (ec == NULL)
		return (0);
	while (format[*pos] != '\0' && format[*pos] != ec[0]
			&& format[*pos] != ec[1])
		++(*pos);
	return (format[*pos] == ec[0] || (ec[1] != '\0' && format[*pos] == ec[1]));
}

#ifndef __ULONG_LONG_MAX__
# define __ULONG_LONG_MAX__ (__LONG_LONG_MAX__ << 1 | 1)
#endif

#ifndef __ULONG_MAX__
# define __ULONG_MAX__ (__LONG_MAX__ << 1 | 1)
#endif

#ifndef __UINT_MAX__
# define __UINT_MAX__ (__INT_MAX__ << 1 | 1)
#endif

#ifndef __USHRT_MAX__
# define __USHRT_MAX__ (__SHRT_MAX__ << 1 | 1)
#endif

#ifndef __UCHAR_MAX__
# define __UCHAR_MAX__ (__CHAR_MAX__ << 1 | 1)
#endif

int			sf_dn_put_arg(t_printf_put_arg *parg, int formn, size_t len, int fd)
{
	size_t			limit;
	t_printf_form	form;

	limit = parg->size - len;
	form = parg->forms[formn];
	sf_jump_form(form.type, parg->format, &parg->pos);
	if (form.type & (PT_D | PT_I))
	{
		if (form.tlength == PTL_INT128)
			return (putn_i128_fd(form.arg.i, fd, limit));
		if (form.tlength == PTL_LONGL)
			return (putn_llong_fd(form.arg.i, fd, limit));
		if (form.tlength == PTL_LONG)
			return (putn_long_fd(form.arg.i, fd, limit));
		if (form.tlength == PTL_INT)
			return (putn_int_fd(form.arg.i, fd, limit));
		if (form.tlength == PTL_SHORT)
			return (putn_short_fd(form.arg.i, fd, limit));
		if (form.tlength == PTL_CHAR)
			return (putn_char_fd(form.arg.i, fd, limit));
	}
	if (form.type == PT_X)
	{
		if (form.tlength == PTL_INT128)
			return (putn_x128_fd(form.arg.ui, fd, limit, form.attr & PA_MAJ));
		if (form.tlength == PTL_LONGL)
			return (putn_x128_fd(form.arg.ui & __ULONG_LONG_MAX__, fd, limit, form.attr & PA_MAJ));
		if (form.tlength == PTL_LONG)
			return (putn_x128_fd(form.arg.ui & __ULONG_MAX__, fd, limit, form.attr & PA_MAJ));
		if (form.tlength == PTL_INT)
			return (putn_x128_fd(form.arg.ui & __UINT_MAX__, fd, limit, form.attr & PA_MAJ));
		if (form.tlength == PTL_SHORT)
			return (putn_x128_fd(form.arg.ui & __USHRT_MAX__, fd, limit, form.attr & PA_MAJ));
		if (form.tlength == PTL_CHAR)
			return (putn_x128_fd(form.arg.ui & __UCHAR_MAX__, fd, limit, form.attr & PA_MAJ));
	}
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
			if (parg.forms == NULL && !(tmp = 0))
				if ((parg.forms = sf_parse_forms(format + parg.pos - 1,
					ap, &tmp)) == NULL || sf_parse_args(parg.forms, ap, tmp))
					return (-1);
			len += sf_dn_put_arg(&parg, formn++, len, fd);
		}
		else
			len += write(fd, format + parg.pos, 1);
//	printf("\n\nformn: %d\n", formn);
	ft_free(parg.forms);
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

//	170141183460469231731687303715884105727

	t_128 test1 = {.i64[0] = 0xFFFFFFFFFFFFFFFF, .i64[1] = 0xFFFFFFFFFFFFFFFF
					//.i64[0] = 0x0000000f00000000, .i64[1] = 0x8000000000000000
				};
	t_int128 test2 = 42;
	t_int128 test0 = -3;
	long	test3;
//	test3 = 0x8000000000000000;
//	test3 = 0x7FFFFFFFFFFFFFFF;
	test3 = -57;
//	int	test3 = -57;

	ft_printf("ft_printf: \ntest2: %2$Md\ntest3: %3$Md\ntest1: %1$Md\ntestd: %Md\ntestd: %d\ntestd: %d\ntestd: %lX\ntest4: %4$X", test0, test1, test2, test3);
	int	_test1 = -1;
	int	_test2 = 42;
	int	_test0 = -3;
	int	_test3 = -57;
	printf("\nprintf: \ntest2: %2$d\ntest3: %3$d\ntest1: %1$d\ntestd: %d\ntestd: %d\ntestd: %d\ntestd: %d\n", _test0, _test1, _test2, _test3);
	//printf utilise une alloc de moins que ft_printf dans ce test, mais le mien s'explique par la gestion des arguments int128 et sans doute bientot long double
	//mon parcours est lineaire, la ou printf (pour les sources que j'ai vu) est particulier (pour ne pas dire bordelique pour les $)
	ft_printf("%ld\n", test3);
	return (0);
}
