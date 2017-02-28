/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 18:15:18 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/28 02:24:09 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//gcc -D__T_FLOAT_SIZE=8 printf.c && ./a.out && clang -D__T_FLOAT_SIZE=8 printf.c && ./a.out
//gcc -D__T_FLOAT_SIZE=8 -I../libft/inc printf.c ../libft/libft.a && ./a.out

#include <ft_printf.h>

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

int	sf_parse_attributes_0(const char *format, int *pos, int *arg_number,
						t_printf_form *out)
{
	int				tmp;

	while (ft_strcchr("%dDioOuUxXeEfFgGaAcCsSpnmbB", format[*pos]) == -1)
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
		else if (format[*pos] == 'v')
			++(*pos) && (tmp = parse_number(format, &out->array, arg_number,
				pos) == -1) ? (out->array = 0) :
							(out->ind_array = tmp);
		else if (format[*pos] == '*' ||
				(format[*pos] >= '1' && format[*pos] <= '9'))
			out->ind_field = parse_number(format, &out->field, arg_number, pos);
		else if ((tmp = ft_strcchr("hlLjztM", format[*pos])) != -1 && ++(*pos))
			out->tlength |= 1 << (tmp + 7 * (((tmp == 0 && format[*pos] == 'h')
					|| (tmp == 1 && format[*pos] == 'l')) && !(0 & ++(*pos))));
		else
			return (-1);
	return (0);
}

char	*thousands_sep(void)
{
	return (localeconv()->thousands_sep);
}

int	sf_validate_form(t_printf_form *form)
{
	int	out;
	int	i;

	out = 0;
	if (form->attr & PA_AQ && form->type & ~(PT_F | PT_D | PT_I) && ++out)
		form->attr &= ~PA_AQ;
	if (form->attr & PA_I && form->type & ~(PT_I | PT_D | PT_U) && ++out)
		form->attr &= ~PA_I;
	(form->array < -1 && ++out) ? (form->array = -1) : 0;
	(form->precision < -1 && ++out) ? (form->precision = -1) : 0;
	(form->field < 0 && ++out) ? (form->field = 0) : 0;
	i = 10;
	while (i--)
		(form->tlength & 1 << i) ? (form->tlength = 1 << i) : 0;
	if (form->type & PT_AF && ++out)
		form->tlength &= (PTL_LONG | PTL_LONGD);
	if (form->type & (PT_C | PT_S) && ++out)
		form->tlength &= PTL_LONG;
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
	if (form->precision != -1 && form->type & ~(PT_AF | PT_AD) && ++out)
		form->precision = -1;
	if (form->attr & PA_HASH && form->type & ~(PT_AF | PT_AC) && ++out)
		form->attr &= ~PA_HASH;
	if (form->attr & PA_ZERO && (form->type & PT_N || form->precision != -1))
		form->attr &= ~PA_ZERO | (0 * ++out);
	if (form->attr & PA_MINUS && form->type & PT_N && ++out)
		form->attr &= ~PA_MINUS;
	if (form->attr & PA_SPACE && form->type & ~(PT_AF | PT_D | PT_I) && ++out)
		form->attr &= ~PA_SPACE;
	if (form->attr & PA_PLUS && form->type & ~(PT_AF | PT_D | PT_I) && ++out)
		form->attr &= ~PA_PLUS;
	return (form->valid = (out == 0 && sf_validate_form(form)));
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
		(ft_strcchr("DUCS", format[*pos]) != -1) ? (form->tlength |= PTL_LONG) :
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
//	debug_printf_forms(out);
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

void		buff_space(t_printf_data *data, size_t size)
{
	(void)data;
	while (size-- > 0)
//		bufferize_char(data, '0');
		write(1, " ", 1);
}

void		buff_zero(t_printf_data *data, size_t size)
{
	(void)data;
	while (size-- > 0)
//		bufferize_char(data, '0');
		write(1, "0", 1);
}

void		buff_i128(t_printf_data *data, t_printf_form *form)
{
	int	size;
//	int	tmp;
//	const static char	tab[] = "0123456789";

	size = ft_evaluate_i128_size(form->arg.i);
	(form->field < size) ? (form->field = size) : 0;
	(form->precision < size) ? (form->precision = size) : 0;
	if (form->arg.i >= 0 && form->attr & (PA_SPACE | PA_PLUS))
		++size;
	if (!(form->attr & PA_MINUS) && form->precision < form->field)
		buff_space(data, form->field - form->precision);
	if (form->attr & PA_SPACE && form->arg.i >= 0)
//		bufferize_char(data, ' ');
		write(1, " ", 1);
	if (form->attr & PA_PLUS && form->arg.i >= 0)
//		bufferize_char(data, '+');
		write(1, "+", 1);
	if (size < form->precision)
		buff_zero(data, form->precision - size);
	if (form->arg.i >= 0 && form->attr & (PA_SPACE | PA_PLUS))
		--size;
	putn_i128_fd(form->arg.i, 1, size);
//	tmp = 1;
//	while (size-- > 0)
//		tmp *= 10;
//	while (tmp /= 10)
//		bufferize_char(data, "0123456789"[(form->arg.i / tmp) % 10]);
//		write(1, tab + (form->arg.i / tmp) % 10, 1);
	//put

	if (form->attr & PA_MINUS && form->precision < form->field)
		buff_space(data, form->field - form->precision);
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

/*
int			dn_put_arg(t_printf_data *data, t_printf_form *forms, int formn, int *pos)
{
	size_t			limit;
	t_printf_form	form;

	limit = data->max_len - data->len;
	form = forms[formn];
	sf_jump_form(form.type, data->format, pos);
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
			//data->len += write(1, "0", 1);
			bufferize_char(data, '0');
			//data->len += ((form.attr & PA_MAJ) ? write(1, "X", 1) : write(1, "x", 1));
			if (form.attr & PA_MAJ)
				bufferize_char(data, 'X');
			else
				bufferize_char(data, 'x');
			limit -= 2;
		}
		return (putn_x128_fd(form.arg.ui, data->fss.fd, limit, form.attr & PA_MAJ));
	}
	if (form.type == PT_O)
	{
		if (limit && (form.attr & PA_HASH) && form.arg.ui != 0)
		{
//			data->len += write(1, "0", 1);
			bufferize_char(data, '0');
			--limit;
		}
		return (putn_o128_fd(form.arg.ui, data->fss.fd, limit));
	}
	if (form.type == PT_B)
	{
		if (limit > 1 && (form.attr & PA_HASH) && form.arg.ui != 0)
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
	}
	return (0);
}
*/
