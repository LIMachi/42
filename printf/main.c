/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 18:49:10 by hmartzol          #+#    #+#             */
/*   Updated: 2017/03/19 08:59:11 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <stdio.h>
#include <ft_int.h>

char	*thousands_sep(void)
{
	return (localeconv()->thousands_sep);
}

int	main()
{
	__int128_t t[40];
	for (int i = 0; i < 40; ++i)
		t[i] = ft_pow10_i128(i);
	ft_printf("%78v40Mu\n", t);
	return (0);
}
