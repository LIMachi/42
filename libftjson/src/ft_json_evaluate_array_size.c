/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_json_evaluate_array_size.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 17:50:27 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/27 07:55:29 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftjson.h>
#include <libft.h>

unsigned long	ft_json_evaluate_array_size(const char *src,
								const unsigned long length, unsigned long pos)
{
	unsigned long	count;
	unsigned long	*c;

	c = (unsigned long[4]){(src[pos++] == '['), 0, 0, 0};
	while (pos < length && ft_isspace(src[pos]))
		++pos;
	count = 1;
	if (src[pos] == ']')
		return (0);
	while (pos < length && c[0])
	{
		if (src[pos] == ',' && c[0] == 1 && !c[1] && !c[2] && !c[3])
			++count;
		c[0] += (src[pos] == '[') - (src[pos] == ']');
		c[1] += (src[pos] == '{') - (src[pos] == '}');
		if (src[pos] == '\"' && src[pos - 1] != '\\')
			c[2] ^= 1;
		if (src[pos] == '\'' && src[pos - 1] != '\\')
			c[3] ^= 1;
		++pos;
	}
	return (count);
}
