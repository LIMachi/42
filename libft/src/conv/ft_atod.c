/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 21:12:31 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/14 23:05:59 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

double	ft_atod(const char *str)
{
	double	out;
	double	sign;
	double	exponent;
	char	*p_tmp;

	p_tmp = (char*)str;
	out = 0.0;
	while (ft_isspace(*p_tmp))
		++p_tmp;
	sign = 1.0;
	if (*p_tmp == '+' || *p_tmp == '-')
		sign = (*p_tmp++ == '-') ? -1.0 : 1.0;
	while (ft_isdigit(*p_tmp))
		out = 10.0 * out + (double)(*p_tmp++ - '0');
	if (*p_tmp == '.' && (exponent = 1.0))
		while (ft_isdigit(*++p_tmp) && (exponent /= 10.0))
			out += exponent * (double)(*p_tmp - '0');
	if (*p_tmp == 'e' || *p_tmp == 'E')
		return (sign * out * ft_powd(10.0, (double)ft_atoi(++p_tmp)));
	return (sign * out);
}
