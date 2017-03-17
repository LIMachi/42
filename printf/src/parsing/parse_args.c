/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 08:59:40 by hmartzol          #+#    #+#             */
/*   Updated: 2017/03/17 07:32:06 by hmartzol         ###   ########.fr       */
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
	if (form->array != -1)
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
	{
		ft_free(forms);
		return (-1);
	}
	i = -1;
	while (forms[++i].arg.ui != (__uint128_t)-1)
		args[forms[i].arg.ui].ui =
			(forms[i].tlength > 8 && forms[i].array == -1);
	i = -1;
	while (++i < argn)
		(args[i].ui) ? (args[i].ui = va_arg(ap, __uint128_t)) :
						(args[i].ui = va_arg(ap, __UINT64_TYPE__));
	i = -1;
	while(forms[++i].arg.ui != (__uint128_t)-1)
		sf_form_add_arg(forms + i, args);
//	debug_printf_forms(forms);
	ft_free(args);
	return (0);
}
