/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_evaluate_i128_size.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lee <lee@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 18:24:20 by lee               #+#    #+#             */
/*   Updated: 2017/03/17 05:28:06 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/*
size_t	ft_evaluate_i128_size(__int128_t v)
{
	if (v == 0)
		return (1);
	if (v < 0)
	{
		if (v == -1)
			return (2);
		return (1 + ft_evaluate_u128_size(-v));
	}
	return ft_evaluate_u128_size(v);
}
*/

size_t	ft_evaluate_i128_size(__int128_t v)
{
	size_t		l;
	__uint128_t	t;

	if (v == 0)
		return (1);
	if (v == -1)
		return (2);
	if (v < 0)
	{
		l = 2;
		t = -v;
	}
	else
	{
		l = 1;
		t = v;
	}
	while (t /= 10)
		++l;
	return (l);
}
