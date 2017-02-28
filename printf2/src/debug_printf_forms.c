/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_printf_forms.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 20:01:36 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/28 01:54:45 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void	print_binary(__T_FLOAT_UI v, int bites)
{
	while (bites--)
		printf("%d", (int)(v >> bites) & 1);
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
