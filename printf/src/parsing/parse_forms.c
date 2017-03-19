/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_forms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 08:07:14 by hmartzol          #+#    #+#             */
/*   Updated: 2017/03/19 08:20:35 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <ft_int.h>

inline static t_printf_form	*sf_prepare_forms(const char *format)
{
	int				count;
	int				i;
	t_printf_form	*out;

	count = 0;
	i = -1;
	while (format[++i] != '\0' && format[i + 1] != '\0')
		if (format[i] == '%' && format[++i] != '%' &&
				format[i] != '{' && format[i] != '}')
			++count;
	if ((out = ft_memalloc(sizeof(t_printf_form) * (count + 1))) == NULL)
		return (NULL);
	out[count].arg.ui = -1;
	return (out);
}

inline static t_printf_form	*sf_validate_form0(t_printf_form *form)
{
	if (form->attr & PA_I && form->type & ~(PT_I | PT_D | PT_U))
		form->attr &= ~PA_I;
	(form->array < -1) ? (form->array = -1) : 0;
	(form->precision < -1) ? (form->precision = -1) : 0;
	(form->field < 0) ? (form->field = 0) : 0;
	if (form->tlength == 0 && form->type & PT_AP)
		form->tlength = __SIZEOF_CHAR__;
	if (form->tlength == 0 && form->type & PT_AF)
		form->tlength = __SIZEOF_DOUBLE__;
	if (form->tlength == 0 && form->type & PT_AD)
		form->tlength = __SIZEOF_INT__;
	if (form->tlength == 0 && PT_C)
		form->tlength = __SIZEOF_CHAR__;
	return (form);
}

inline static t_printf_form	*sf_validate_form(t_printf_form *form)
{
	if (form->type & (PT_N | PT_M) && (form->precision < -1 ||
							form->field < 0 || form->array < -1))
	{
		form->precision = -1;
		form->field = 0;
		form->array = -1;
	}
	if (form->array != -1 && form->type & (PT_NP | PT_M))
		form->array = -1;
	if (form->attr & PA_ZERO && (form->type & PT_N || form->precision != -1))
		form->attr &= ~PA_ZERO;
	if (form->attr & PA_MINUS && form->type & PT_N)
		form->attr &= ~PA_MINUS;
	if (form->attr & PA_SPACE && form->type & ~(PT_AF | PT_D | PT_I))
		form->attr &= ~PA_SPACE;
	if (form->attr & PA_PLUS && form->type & ~(PT_AF | PT_D | PT_I))
		form->attr &= ~PA_PLUS;
	return (sf_validate_form0(form));
}

t_printf_form				*parse_forms(const char *format, int *argn)
{
	t_printf_form	*out;
	int				i;
	int				j;
	int				tmp;
	int				argc;

	if ((i = -1) && (out = sf_prepare_forms(format)) == NULL)
		return (NULL);
	argc = 0;
	j = 0;
	while (format[++i] != '\0')
	{
		if (format[i] == '%' && format[++i] != '%')
		{
			if ((tmp = parse_attributes(format, &i, argn,
				out + j++)) == -1)
			{
				ft_free(out);
				return (NULL);
			}
			argc < tmp ? argc = tmp : 0;
		}
	}
	*argn = argc;
	return (sf_validate_form(out));
}
