/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 18:52:52 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/18 13:58:19 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** note: base can't contain '\0', '+', '-', ' ', '\t' or '\n'
*/

int						ft_atoi_base(const char *str, const int size_base,
															const char *base)
{
	int		out;
	int		sign;
	char	*p_tmp;
	void	*ptr;

	p_tmp = (char*)str;
	out = 0;
	while (ft_isspace(*p_tmp))
		++p_tmp;
	if ((sign = 1) && (*p_tmp == '+' || *p_tmp == '-'))
		sign = (*p_tmp++ == '-') ? -1 : 1;
	while (*p_tmp && (ptr = ft_memchr(base, *p_tmp++, size_base)))
		out = size_base * out + (int)((char *)ptr - (char *)base);
	return (out * sign);
}
