/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 18:15:18 by hmartzol          #+#    #+#             */
/*   Updated: 2017/03/17 09:44:11 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//gcc -D__T_FLOAT_SIZE=8 printf.c && ./a.out && clang -D__T_FLOAT_SIZE=8 printf.c && ./a.out
//gcc -D__T_FLOAT_SIZE=8 -I../libft/inc printf.c ../libft/libft.a && ./a.out

#include <ft_printf.h>
#include <ft_int.h>

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

void	sf_parse_length_attribute(const char *str, int *pos, t_printf_form *out)
{
	if (str[*pos] == 'h')
		out->tlength = (out->tlength == __SIZEOF_SHORT__) ?
				__SIZEOF_CHAR__ : __SIZEOF_SHORT__;
	if (str[*pos] == 'l')
		out->tlength = (out->tlength == __SIZEOF_LONG__) ?
				__SIZEOF_LONG_LONG__ : __SIZEOF_LONG__;
	if (str[*pos] == 'L')
		out->tlength = __SIZEOF_LONG_DOUBLE__;
	if (str[*pos] == 'j')
		out->tlength = __SIZEOF_INTMAX_T__;
	if (str[*pos] == 'z')
		out->tlength = __SIZEOF_SIZE_T__;
	if (str[*pos] == 't')
		out->tlength = __SIZEOF_PTRDIFF_T__;
	if (str[*pos] == 'M')
		out->tlength = __SIZEOF_INT128__;
	++(*pos);
}

int	sf_parse_attributes_0(const char *str, int *pos, int *arg_number,
						t_printf_form *out)
{
	int				tmp;

	while (ft_strcchr("%dDioOuUxXeEfFgGaAcCsSpnmbB", str[*pos]) == -1)
		if ((tmp = ft_strcchr("#0- +'I", str[*pos])) != -1 && ++(*pos))
		{
			out->attr |= 1 << tmp;
			out->attr & PA_MINUS ? out->attr &= ~PA_ZERO : 0;
			out->attr & PA_PLUS ? out->attr &= ~PA_SPACE : 0;
		}
		else if (str[*pos] == '.' && !(0 & (out->attr &= ~PA_ZERO)))
			++(*pos) && ((tmp = parse_number(str, &out->precision, arg_number,
				pos)) == -1) ? (out->precision = -1) :
							(out->ind_precision = tmp);
		else if (str[*pos] == 'v')
			++(*pos) && ((tmp = parse_number(str, &out->array, arg_number,
				pos)) == -1) ? (out->array = 0) :
							(out->ind_array = tmp);
		else if (str[*pos] == '*' || (str[*pos] >= '1' && str[*pos] <= '9'))
			out->ind_field = parse_number(str, &out->field, arg_number, pos);
		else if (ft_strcchr("hlLjztM", str[*pos]) != -1)
			sf_parse_length_attribute(str, pos, out);
		else
			return (-1);
	return (0);
}

int	sf_validate_form(t_printf_form *form)
{
	int	out;
//	int	i;

	out = 0;
//	if (form->attr & PA_AQ && form->type & ~(PT_F | PT_D | PT_I) && ++out)
//		form->attr &= ~PA_AQ;
	if (form->attr & PA_I && form->type & ~(PT_I | PT_D | PT_U) && ++out)
		form->attr &= ~PA_I;
	(form->array < -1 && ++out) ? (form->array = -1) : 0;
	(form->precision < -1 && ++out) ? (form->precision = -1) : 0;
	(form->field < 0 && ++out) ? (form->field = 0) : 0;
	if (form->tlength == 0 && form->type & PT_AP)
		form->tlength = __SIZEOF_CHAR__;
	if (form->tlength == 0 && form->type & PT_AF)
		form->tlength = __SIZEOF_DOUBLE__;
	if (form->tlength == 0 && form->type & PT_AD)
		form->tlength = __SIZEOF_INT__;
	if (form->tlength == 0 && PT_C)
		form->tlength = __SIZEOF_CHAR__;
//	i = 10;
	// while (i--)
	// 	(form->tlength & 1 << i) ? (form->tlength = 1 << i) : 0;
	// if (form->type & PT_AF && ++out)
	// 	form->tlength &= (PTL_DOUBLE | PTL_LDOUBLE);
	// if (form->type & (PT_C | PT_S) && ++out)
	// 	form->tlength &= PTL_LONG;
	return (out == 0);
}

int	validate_form(t_printf_form *form)
{
	int	out;

	out = 0;
	if (form->type & (PT_N | PT_M) && (form->precision < -1 ||
							form->field < 0 || form->array < -1) && ++out)
	{
		form->precision = -1;
		form->field = 0;
		form->array = -1;
	}
	if (form->array != -1 && form->type & (PT_NP | PT_M) && ++out)
		form->array = -1;
//	if (form->precision != -1 && form->type & ~(PT_AF | PT_AD) && ++out)
//		form->precision = -1;
//	if (form->attr & PA_HASH && form->type & ~(PT_AF | PT_AC) && ++out)
//		form->attr &= ~PA_HASH;
	if (form->attr & PA_ZERO && (form->type & PT_N || form->precision != -1))
		form->attr &= ~PA_ZERO | (0 * ++out);
	if (form->attr & PA_MINUS && form->type & PT_N && ++out)
		form->attr &= ~PA_MINUS;
	if (form->attr & PA_SPACE && form->type & ~(PT_AF | PT_D | PT_I) && ++out)
		form->attr &= ~PA_SPACE;
	if (form->attr & PA_PLUS && form->type & ~(PT_AF | PT_D | PT_I) && ++out)
		form->attr &= ~PA_PLUS;
	return (form->valid = (sf_validate_form(form) && out == 0));
}

int	sf_parse_attributes(const char *format, int *pos, int *arg_number,
						t_printf_form *form)
{
	int		tmp;
	int		out;

	*form = (t_printf_form){.attr = 0, .ind_field = 0, .ind_precision = 0,
		.ind_array = 0, .field = 0, .precision = -1, .tlength = 0, .type = 0,
		.array = -1, .arg.ui = -1};
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
	if ((tmp = ft_strcchr("%diouxefgacspnmb", format[*pos])) != -1)
		form->type = 1 << (tmp - 1);
	else if (ft_strcchr("DUXEFGACSB", format[*pos]) != -1)
	{
		(ft_strcchr("DUCS", format[*pos]) != -1) ? (form->tlength = __SIZEOF_LONG__) :
												(form->attr |= PA_MAJ);
									//"%diouxefgacspnmb"
		form->type = 1 << (ft_strcchr(" D  UXEFGACS   B", format[*pos]) - 1);
	}
	else
		return (-1);
	if (form->type == PT_PERCENT || form->type == PT_M)
	{
		if (form->arg.ui != (__uint128_t)-1)
			return (-1);
	}
	else
		if (form->arg.ui == (__uint128_t)-1)
			form->arg.ui = (*arg_number)++;
	/*if (!*/validate_form(form)/*)*/;
//		return (-1);
	out = *arg_number >= (int)form->arg.ui ? *arg_number : (int)form->arg.ui;
	form->ind_precision && out < form->precision ? out = form->precision : 0;
	form->ind_array && out < form->array ? out = form->array : 0;
	return (1 + (form->ind_field && out < form->field ? form->field : out));
}

t_printf_form	*parse_forms(const char *format, int *argn)
{
	t_printf_form	*out;
	int				i;
	int				j;
	int				tmp;
	int				argc;

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
	debug_printf_forms(out);
	return (out);
}

int			sf_putn_b128_fd(__uint128_t v, int fd, size_t n)
{
	static const char	tab[] = "01";

	if (n == 0)
		return (0);
	if (v == 0)
		return (0);
	return (sf_putn_b128_fd(v >> 1, fd, n - 1)
				+ write(fd, &tab[v & 1], 1));
//			bufferize_char(t_printf_data *data, char c));
}

int			putn_b128_fd(__uint128_t v, int fd, size_t n)
{
	if (n == 0)
		return (0);
	if (v == 0)
		return (write(fd, "0", 1));
	return (sf_putn_b128_fd(v, fd, n));
}

int			sf_putn_o128_fd(__uint128_t v, int fd, size_t n)
{
	static const char	tab[] = "01234567";

	if (n == 0)
		return (0);
	if (v == 0)
		return (0);
	return (sf_putn_o128_fd(v >> 3, fd, n - 1)
				+ write(fd, &tab[v & 7], 1));
}

int			putn_o128_fd(__uint128_t v, int fd, size_t n)
{
	if (n == 0)
		return (0);
	if (v == 0)
		return (write(fd, "0", 1));
	return (sf_putn_o128_fd(v, fd, n));
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
		return (sf_putn_x128_fd(v >> 4, fd, n - 1, maj)
				+ write(fd, &tabm[v & 15], 1));
	return (sf_putn_x128_fd(v >> 4, fd, n - 1, maj)
			+ write(fd, &tab[v & 15], 1));
}

int			putn_x128_fd(__uint128_t v, int fd, size_t n, int maj)
{
	if (n == 0)
		return (0);
	if (v == 0)
		return (write(fd, "0", 1));
	return (sf_putn_x128_fd(v, fd, n, maj));
}

/*
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
*/

/*
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
*/

int			sf_putn_u128_fd(t_printf_data *data, __uint128_t v, size_t n)
{
	if (n == 0)
		return (0);
	if (v == 0)
		return (0);
	return (sf_putn_u128_fd(data, v / 10, n - 1) + bufferize_char(data, "0123456789"[v % 10]));
}

int			putn_u128_fd(t_printf_data *data, __uint128_t v, size_t n)
{
	if (n == 0)
		return (0);
	if (v == 0)
		return (bufferize_char(data, '0'));
	return (sf_putn_u128_fd(data, v, n));
}

void	sf_buff_o128(t_printf_data *data, __uint128_t v)
{
	int s;

	if (v == 0)
	{
		bufferize_char(data, '0');
		return ;
	}
	s = 0;
	while (s < 48 && v >= (__uint128_t)1 << (s * 3))
		++s;
	while (s--)
		bufferize_char(data, '0' + ((v >> (s * 3)) & 7));
}

void	sf_buff_b128(t_printf_data *data, __uint128_t v)
{
	int s;

	if (v == 0)
	{
		bufferize_char(data, '0');
		return ;
	}
	s = 0;
	while (s < 128 && v >= (__uint128_t)1 << s)
		++s;
	while (s--)
		bufferize_char(data, '0' + ((v >> s) & 1));
}

void	sf_buff_x128(t_printf_data *data, __uint128_t v, int maj)
{
	int s;

	if (v == 0)
	{
		bufferize_char(data, '0');
		return ;
	}
	s = 0;
	while (s < 32 && v >= (__uint128_t)1 << (s << 2))
		++s;
	if (maj)
		while (s--)
			bufferize_char(data, "0123456789ABCDEF"[(v >> (s << 2)) & 0xF]);
	else
		while (s--)
			bufferize_char(data, "0123456789abcdef"[(v >> (s << 2)) & 0xF]);
}

void	sf_buff_u128(t_printf_data *data, __uint128_t v)
{
	int					i;
	static const t_i128	p[39] = {{{1, 0}}, {{10, 0}}, {{100, 0}}, {{1000, 0}},

	{{10000, 0}}, {{100000, 0}}, {{1000000, 0}}, {{10000000, 0}}, {{100000000,
	0}}, {{1000000000, 0}}, {{10000000000, 0}}, {{100000000000, 0}},
	{{1000000000000, 0}}, {{10000000000000, 0}}, {{100000000000000, 0}},
	{{1000000000000000, 0}}, {{10000000000000000, 0}}, {{100000000000000000,
	0}}, {{1000000000000000000, 0}}, {{10000000000000000000u, 0}},
	{{0x6bc75e2d63100000, 5}}, {{0x35c9adc5dea00000, 0x36}},
	{{0x19e0c9bab2400000, 0x21e}}, {{0x2c7e14af6800000, 0x152d}},
	{{0x1bcecceda1000000, 0xd3c2}}, {{0x161401484a000000, 0x84595}},
	{{0xdcc80cd2e4000000, 0x52b7d2}}, {{0x9fd0803ce8000000, 0x33b2e3c}},
	{{0x3e25026110000000, 0x204fce5e}}, {{0x6d7217caa0000000, 0x1431e0fae}},
	{{0x4674edea40000000, 0xc9f2c9cd0}}, {{0xc0914b2680000000, 0x7e37be2022}},
	{{0x85acef8100000000, 0x4ee2d6d415b}}, {{0x38c15b0a00000000,
	0x314dc6448d93}}, {{0x378d8e6400000000, 0x1ed09bead87c0}},
	{{0x2b878fe800000000, 0x13426172c74d82}}, {{0xb34b9f1000000000,
	0xc097ce7bc90715}}, {{0xf436a000000000, 0x785ee10d5da46d9}},
	{{0x98a224000000000, 0x4b3b4ca85a86c47a}}};
	i = 0;
	while (i < 40 && v > p[i].u128)
		++i;
	!i ? bufferize_char(data, '0') : 0;
	while (i--)
		bufferize_char(data, "0123456789"[v / p[i].u128 % 10]);
}

void	sf_buff_i128(t_printf_data *data, __int128_t v)
{
	if (v == -1)
	{
		bufferize_char(data, '-');
		bufferize_char(data, '1');
		return ;
	}
	if (v & ((__int128_t)1) << 127)
	{
		bufferize_char(data, '-');
		sf_buff_u128(data, -v);
	}
	else
		sf_buff_u128(data, v);
}

int			putn_i128_fd(t_printf_data *data, __int128_t v, size_t n)
{
	if (n == 0)
		return (0);
	if (v == 0)
		return (bufferize_char(data, '0'));
	if (v & (__int128_t)1 << (__SIZEOF_INT128__ * 8 - 1))
		return (bufferize_char(data, '-') + sf_putn_u128_fd(data, -v, n - 1));
	return (sf_putn_u128_fd(data, v, n));
}

void		buff_space(t_printf_data *data, size_t size)
{
	while (size-- > 0)
		bufferize_char(data, ' ');
}

void		buff_zero(t_printf_data *data, size_t size)
{
	while (size-- > 0)
		bufferize_char(data, '0');
}

/*
void		sf_buff_i128(t_printf_data *data, __int128_t i, int size, int attr)
{
	if (attr & PA_AQ)
}
*/

void		buff_i128(t_printf_data *data, t_printf_form form, __int128_t i)
{
	int	size;
	int	m;

	m = (form.attr & PA_SPACE || form.attr & PA_PLUS);
	size = ft_evaluate_i128_size(i);
	(form.attr & PA_AQ) ? size += (size / 3) : 0;
	(form.field < size) ? (form.field = size) : 0;
	(form.precision < size) ? (form.precision = size) : 0;
	if (!(form.attr & PA_MINUS) && form.precision < form.field)
		buff_space(data, form.field - form.precision - m);
	if (form.attr & PA_SPACE && i >= 0)
		bufferize_char(data, ' ');
	if (form.attr & PA_PLUS && i >= 0)
		bufferize_char(data, '+');
	if (size < form.precision)
		buff_zero(data, form.precision - size);
	sf_buff_i128(data, i);
	if (form.attr & PA_MINUS && form.precision < form.field)
		buff_space(data, form.field - form.precision - m);
}

void		buff_u128(t_printf_data *data, t_printf_form form, __uint128_t ui)
{
	int	size;
	int	m;

	m = (form.attr & PA_SPACE || form.attr & PA_PLUS);
	size = ft_evaluate_u128_size(ui);
	(form.attr & PA_AQ) ? size += (size / 3) : 0;
	(form.field < size) ? (form.field = size) : 0;
	(form.precision < size) ? (form.precision = size) : 0;
	if (!(form.attr & PA_MINUS) && form.precision < form.field)
		buff_space(data, form.field - form.precision - m);
	if (form.attr & PA_SPACE)
		bufferize_char(data, ' ');
	if (form.attr & PA_PLUS)
		bufferize_char(data, '+');
	if (size < form.precision)
		buff_zero(data, form.precision - size);
	sf_buff_u128(data, ui/*, size, form.attr*/);
	if (form.attr & PA_MINUS && form.precision < form.field)
		buff_space(data, form.field - form.precision - m);
}

void		buff_x128(t_printf_data *data, t_printf_form form, __uint128_t ui)
{
	int	size;
	int	m;

	m = (form.attr & PA_HASH) ? 2 : 0;
	size = ft_evaluate_x128_size(ui);
	(form.attr & PA_AQ) ? size += (size / 3) : 0;
	(form.field < size) ? (form.field = size) : 0;
	(form.precision < size) ? (form.precision = size) : 0;
	if (!(form.attr & PA_MINUS) && form.precision < form.field)
		buff_space(data, form.field - form.precision - m);
	if (form.attr & PA_HASH)
	{
		bufferize_char(data, '0');
		bufferize_char(data, form.attr & PA_MAJ ? 'X' : 'x');
	}
	if (size < form.precision)
		buff_zero(data, form.precision - size);
	sf_buff_x128(data, ui, form.attr & PA_MAJ);
	if (form.attr & PA_MINUS && form.precision < form.field)
		buff_space(data, form.field - form.precision - m);
}

void		buff_b128(t_printf_data *data, t_printf_form form, __uint128_t ui)
{
	int	size;
	int	m;

	m = (form.attr & PA_HASH) ? 2 : 0;
	size = ft_evaluate_b128_size(ui);
	(form.attr & PA_AQ) ? size += (size / 3) : 0;
	(form.field < size) ? (form.field = size) : 0;
	(form.precision < size) ? (form.precision = size) : 0;
	if (!(form.attr & PA_MINUS) && form.precision < form.field)
		buff_space(data, form.field - form.precision - m);
	if (form.attr & PA_HASH)
	{
		bufferize_char(data, '0');
		bufferize_char(data, form.attr & PA_MAJ ? 'B' : 'b');
	}
	if (size < form.precision)
		buff_zero(data, form.precision - size);
	sf_buff_b128(data, ui);
	if (form.attr & PA_MINUS && form.precision < form.field)
		buff_space(data, form.field - form.precision - m);
}

void		buff_o128(t_printf_data *data, t_printf_form form, __uint128_t ui)
{
	int	size;
	int	m;

	m = ((form.attr & PA_HASH) && ui);
	size = ft_evaluate_o128_size(ui);
	(form.attr & PA_AQ) ? size += (size / 3) : 0;
	(form.field < size) ? (form.field = size) : 0;
	(form.precision < size) ? (form.precision = size) : 0;
	if (!(form.attr & PA_MINUS) && form.precision < form.field)
		buff_space(data, form.field - form.precision - m);
	if ((form.attr & PA_HASH) && ui)
		bufferize_char(data, '0');
	if (size < form.precision)
		buff_zero(data, form.precision - size);
	sf_buff_o128(data, ui);
	if (form.attr & PA_MINUS && form.precision < form.field)
		buff_space(data, form.field - form.precision - m);
}

int		buff_ce(t_printf_data *data, __uint128_t c)
{
	c &= 0xFF;
	if (c < 0x20 || c > 0x7E)
	{
		bufferize_char(data, '\\');
		if (c == '\a')
			return (bufferize_char(data, 'a'));
		if (c == '\b')
			return (bufferize_char(data, 'b'));
		if (c == '\t')
			return (bufferize_char(data, 't'));
		if (c == '\n')
			return (bufferize_char(data, 'n'));
		if (c == '\v')
			return (bufferize_char(data, 'v'));
		if (c == '\f')
			return (bufferize_char(data, 'f'));
		if (c == '\r')
			return (bufferize_char(data, 'r'));
		bufferize_char(data, 'x');
		sf_buff_x128(data, c, 1);
	}
	else
		bufferize_char(data, c);
	return (0);
}

void		buff_c128(t_printf_data *data, t_printf_form form, __uint128_t ui)
{
	if (form.attr & PA_AQ)
		bufferize_char(data, '\'');
	if (form.tlength == __SIZEOF_CHAR__)
	{
		if (form.attr & PA_HASH)
			buff_ce(data, ui);
		else
			bufferize_char(data, (char)ui);
	}
//	if (form.tlength == __SIZEOF_WCHAR_T__)
//		bufferize_wchar(data, ui);
	if (form.attr & PA_AQ)
		bufferize_char(data, '\'');
}

void		buff_s128(t_printf_data *data, t_printf_form form, char *str)
{
	char	*ptr;
	int		size;
	int		i;

	ptr = str;
//	printf("%p\n", ptr);
	if (form.attr & PA_AQ)
		bufferize_char(data, '\"');
	if (form.tlength == __SIZEOF_CHAR__)
	{
		size = ft_strlen(ptr);
		(form.field < size) ? (form.field = size) : 0;
//		printf("\nprecision %d\n", form.precision);
		(form.precision > -1 && form.precision < size) ? (size = form.precision) : 0;
		if (!(form.attr & PA_MINUS) && size < form.field)
			buff_space(data, form.field - size);
		i = 0;
		if (form.attr & PA_HASH)
			while (i < size && ptr[i] != '\0')
				buff_ce(data, ptr[i++]);
		else
			while (i < size && ptr[i] != '\0')
				bufferize_char(data, ptr[i++]);
		if (form.attr & PA_MINUS && size < form.field)
			buff_space(data, form.field - size);
	}
	// if (form.tlength == __SIZEOF_WCHAR_T__)
	// 	while (*(wchar_t*)ptr != NULL_WCHAR_T)
	// 	{
	// 		bufferize_wchar(data, *ptr);
	// 		ptr += __SIZEOF_WCHAR_T__;
	// 	}
	if (form.attr & PA_AQ)
		bufferize_char(data, '\"');
}

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
	type == PT_B ? ec = (char[2]){'b', 'B'} : 0;
	if (ec == NULL)
		return (0);
	while (format[*pos] != '\0' && format[*pos] != ec[0]
			&& format[*pos] != ec[1])
		++(*pos);
	return (format[*pos] == ec[0] || (ec[1] != '\0' && format[*pos] == ec[1]));
}

/*
int			dn_put_arg(t_printf_put_arg *parg, int formn, size_t len, int fd)
{
	size_t			limit;
	t_printf_form	form;

	limit = parg->size - len;
	form = parg->forms[formn];
	sf_jump_form(form.type, parg->format, &parg->pos);
	if (form.type & (PT_D | PT_I))
	{
//			return (putn_i128_fd(form.arg.i, fd, limit));
		buff_i128(NULL, &form);
		return (0);
	}
	if (form.type == PT_X)
	{
		if (limit > 1 && (form.attr & PA_HASH) && form.arg.ui != 0)
		{
			len += write(1, "0", 1);
			len += ((form.attr & PA_MAJ) ? write(1, "X", 1) : write(1, "x", 1));
			limit -= 2;
		}
		return (putn_x128_fd(form.arg.ui, fd, limit, form.attr & PA_MAJ));
	}
	if (form.type == PT_O)
	{
		if (limit && (form.attr & PA_HASH) && form.arg.ui != 0)
		{
			len += write(1, "0", 1);
			--limit;
		}
		return (putn_o128_fd(form.arg.ui, fd, limit));
	}
	if (form.type == PT_B)
	{
		if (limit > 1 && (form.attr & PA_HASH) && form.arg.ui != 0)
		{
			len += write(1, "0", 1);
			len += ((form.attr & PA_MAJ) ? write(1, "B", 1) : write(1, "b", 1));
			limit -= 2;
		}
		return (putn_b128_fd(form.arg.ui, fd, limit));
	}
	return (0);
}
*/
//*
int			dn_put_arg(t_printf_data *data, t_printf_form *forms, int formn, size_t *pos)
{
//	size_t			limit;
	t_printf_form	form;

//	limit = data->size - data->len;
	form = forms[formn];
	sf_jump_form(form.type, data->format, pos);
	if (form.type & (PT_D | PT_I))
	{
		if (form.array == -1)
			buff_i128(data, form, form.arg.i);
		else
		{
			char *ptr = (char *)(long)form.arg.ui;
			bufferize_char(data, '{');
			for (int i = 0; i < form.array; ++i)
			{
				buff_i128(data, form, cast_uint128(*(__uint128_t*)ptr, form.tlength << 3, 1));
				ptr += form.tlength;
				if (i < form.array - 1)
				{
					bufferize_char(data, ',');
					bufferize_char(data, ' ');
				}
			}
			bufferize_char(data, '}');
		}
		return (0);
	}
	if (form.type == PT_U)
	{
		if (form.array == -1)
			buff_u128(data, form, form.arg.ui);
		else
		{
			char *ptr = (char *)(long)form.arg.ui;
			bufferize_char(data, '{');
			for (int i = 0; i < form.array; ++i)
			{
				buff_u128(data, form, cast_uint128(*(__uint128_t*)ptr, form.tlength << 3, 0));
				ptr += form.tlength;
				if (i < form.array - 1)
				{
					bufferize_char(data, ',');
					bufferize_char(data, ' ');
				}
			}
			bufferize_char(data, '}');
		}
		return (0);
	}
	if (form.type == PT_X) ///buff_x128
	{
		if (form.array == -1)
			buff_x128(data, form, form.arg.ui);
		else
		{
			char *ptr = (char *)(long)form.arg.ui;
			bufferize_char(data, '{');
			for (int i = 0; i < form.array; ++i)
			{
				buff_x128(data, form, cast_uint128(*(__uint128_t*)ptr, form.tlength << 3, 0));
				ptr += form.tlength;
				if (i < form.array - 1)
				{
					bufferize_char(data, ',');
					bufferize_char(data, ' ');
				}
			}
			bufferize_char(data, '}');
		}
		return (0);
/*		if (limit > 1 && (form.attr & PA_HASH) && form.arg.ui != 0)
		{
			//data->len += write(1, "0", 1);
			bufferize_char(data, '0');
			//data->len += ((form.attr & PA_MAJ) ? write(1, "X", 1) : write(1, "x", 1));
			if (form.attr & PA_MAJ)
				bufferize_char(data, 'X');
			else
				bufferize_char(data, 'x');
			limit -= 2;
		}
//		return (putn_x128_fd(form.arg.ui, data->fss.fd, limit, form.attr & PA_MAJ));
		sf_buff_x128(data, form.arg.ui, form.attr & PA_MAJ);
		return (0);
*/
	}
	if (form.type == PT_O)
	{
		if (form.array == -1)
			buff_o128(data, form, form.arg.ui);
		else
		{
			char *ptr = (char *)(long)form.arg.ui;
			bufferize_char(data, '{');
			for (int i = 0; i < form.array; ++i)
			{
				buff_o128(data, form, cast_uint128(*(__uint128_t*)ptr, form.tlength << 3, 0));
				ptr += form.tlength;
				if (i < form.array - 1)
				{
					bufferize_char(data, ',');
					bufferize_char(data, ' ');
				}
			}
			bufferize_char(data, '}');
		}
		return (0);
/*		if (limit && (form.attr & PA_HASH) && form.arg.ui != 0)
		{
//			data->len += write(1, "0", 1);
			bufferize_char(data, '0');
			--limit;
		}
		return (putn_o128_fd(form.arg.ui, data->fss.fd, limit));
*/
	}
	if (form.type == PT_B)
	{
		if (form.array == -1)
			buff_b128(data, form, form.arg.ui);
		else
		{
			char *ptr = (char *)(long)form.arg.ui;
			bufferize_char(data, '{');
			for (int i = 0; i < form.array; ++i)
			{
				buff_b128(data, form, cast_uint128(*(__uint128_t*)ptr, form.tlength << 3, 0));
				ptr += form.tlength;
				if (i < form.array - 1)
				{
					bufferize_char(data, ',');
					bufferize_char(data, ' ');
				}
			}
			bufferize_char(data, '}');
		}
		return (0);
/*		if (limit > 1 && (form.attr & PA_HASH) && form.arg.ui != 0)
		{
//			data->len += write(1, "0", 1);
//			data->len += ((form.attr & PA_MAJ) ? write(1, "B", 1) : write(1, "b", 1));
			bufferize_char(data, '0');
			if (form.attr & PA_MAJ)
				bufferize_char(data, 'B');
			else
				bufferize_char(data, 'b');
			limit -= 2;
		}
		return (putn_b128_fd(form.arg.ui, data->fss.fd, limit));
*/
	}
	if (form.type == PT_C)
	{
		if (form.array == -1)
			buff_c128(data, form, form.arg.ui);
		else
		{
			char *ptr = (char *)(long)form.arg.ui;
			bufferize_char(data, '{');
			for (int i = 0; i < form.array; ++i)
			{
				buff_c128(data, form, cast_uint128(*(__uint128_t*)ptr, form.tlength << 3, 0));
				ptr += form.tlength;
				if (i < form.array - 1)
				{
					bufferize_char(data, ',');
					bufferize_char(data, ' ');
				}
			}
			bufferize_char(data, '}');
		}
		return (0);
	}
	if (form.type == PT_S)
	{
		if (form.array == -1)
			buff_s128(data, form, (char*)(long)form.arg.ui);
		else
		{
			char **ptr = (char **)(long)form.arg.ui;
			bufferize_char(data, '{');
			for (int i = 0; i < form.array; ++i)
			{
				buff_s128(data, form, *ptr);
				++ptr;
				if (i < form.array - 1)
				{
					bufferize_char(data, ',');
					bufferize_char(data, ' ');
				}
			}
			bufferize_char(data, '}');
		}
		return (0);
	}
	return (0);
}
//*/
