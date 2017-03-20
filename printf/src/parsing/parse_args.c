/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 08:59:40 by hmartzol          #+#    #+#             */
/*   Updated: 2017/03/20 11:35:35 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <ft_int.h>

void	sf_form_add_arg(t_printf_form *form, t_printf_arg *args)
{
	if (form->ind_field)
		form->field = args[form->field].ui;
	if (form->ind_precision)
		form->precision = args[form->precision].ui;
	if (form->ind_array)
		form->array = args[form->array].ui;
	if (form->array != -1 || form->type & PT_AP)
		form->arg.ui = cast_uint128(args[form->arg.ui].ui,
						__SIZEOF_POINTER__ << 3, 0);
	else
		form->arg.ui = cast_uint128(args[form->arg.ui].ui,
						form->tlength << 3, ((form->type & PT_AS) != 0));
}

int		parse_args(t_printf_form *forms, va_list ap, int argn)
{
	t_printf_arg	*args;
	int				i;

	if ((args = ft_memalloc(sizeof(t_printf_arg) * argn)) == NULL)
		return (-1 | (long)ft_free(forms));
	i = -1;
	while (forms[++i].arg.ui != (__uint128_t)-1)
		if (forms[i].array == -1)
			args[forms[i].arg.ui].ui = !(forms[i].type & PT_AF) ?
				(forms[i].tlength > 8 && forms[i].array == -1) :
				2 + (forms[i].tlength == __SIZEOF_LONG_DOUBLE__);
	i = -1;
	while (++i < argn)
		if (args[i].ui == 1)
			args[i].ui = va_arg(ap, __uint128_t);
		else if (args[i].ui == 2)
			args[i].f = va_arg(ap, double);
		else if (args[i].ui == 3)
			args[i].ld = va_arg(ap, long double);
		else
			args[i].ui = va_arg(ap, __UINT64_TYPE__);
	i = -1;
	while(forms[++i].arg.ui != (__uint128_t)-1)
		sf_form_add_arg(forms + i, args);
	return ((long)ft_free(args));
}
