/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 08:59:40 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/26 09:00:00 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void	sf_form_add_arg(t_printf_form *form, t_printf_arg *args)
{
	if (form->ind_field)
		form->field = args[form->field].ui;
	if (form->ind_precision)
		form->precision = args[form->precision].ui;
	form->tlength == PTL_INT ? form->arg.ui = (int)args[form->arg.ui].ui : 0;
	if (form->tlength == PTL_SHORT)
		form->arg.ui = (short)args[form->arg.ui].ui;
	form->tlength == PTL_LONG ? form->arg.ui = (long)args[form->arg.ui].ui : 0;
	form->tlength == PTL_LONGD ? form->arg.ui = args[form->arg.ui].ui : 0;
	if (form->tlength == PTL_INTMAX)
		form->arg.ui = (intmax_t)args[form->arg.ui].ui;
	if (form->tlength == PTL_SSIZE)
		form->arg.ui = (ssize_t)args[form->arg.ui].ui;
	if (form->tlength == PTL_PTRDIFF)
		form->arg.ui = (ptrdiff_t)args[form->arg.ui].ui;
	form->tlength == PTL_INT128 ? form->arg.ui = args[form->arg.ui].ui : 0;
	form->tlength == PTL_CHAR ? form->arg.ui = (char)args[form->arg.ui].ui : 0;
	if (form->tlength == PTL_LONGL)
		form->arg.ui = (long long)args[form->arg.ui].ui;
}

int		parse_args(t_printf_form *forms, va_list ap, int argn)
{
	t_printf_arg	*args;
//	int				tmp;
	int				i;

	if ((args = ft_memalloc(sizeof(t_printf_arg) * argn)) == NULL)
	{
		ft_free(forms);
		return (-1);
	}
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
