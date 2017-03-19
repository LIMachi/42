/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 18:15:18 by hmartzol          #+#    #+#             */
/*   Updated: 2017/03/19 08:25:49 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <ft_int.h>

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

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__

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
	while (i < 39 && v >= p[i].u128)
		++i;
	!i ? bufferize_char(data, '0') : 0;
	while (i--)
		bufferize_char(data, "0123456789"[(v / p[i].u128) % 10]);
}

#else
# if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__

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
	while (i < 39 && v >= p[i].u128)
		++i;
	!i ? bufferize_char(data, '0') : 0;
	while (i--)
		bufferize_char(data, "0123456789"[(v / p[i].u128) % 10]);
}

# else
#  error "Invalid endian"
# endif
#endif

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
