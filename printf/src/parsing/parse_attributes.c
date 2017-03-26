/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_attributes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 08:15:56 by hmartzol          #+#    #+#             */
/*   Updated: 2017/03/19 08:22:05 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <ft_int.h>

inline static void	sf_parse_length_attribute(const char *str, int *pos,
												t_printf_form *out)
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

inline static int	sf_parse_attributes_0(const char *str, int *pos,
										int *arg_number, t_printf_form *out)
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

int	parse_attributes(const char *format, int *pos, int *arg_number,
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
	out = *arg_number >= (int)form->arg.ui ? *arg_number : (int)form->arg.ui;
	form->ind_precision && out < form->precision ? out = form->precision : 0;
	form->ind_array && out < form->array ? out = form->array : 0;
	return (1 + (form->ind_field && out < form->field ? form->field : out));
}
