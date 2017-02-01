/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_json_evaluate_value_type.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 17:46:30 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/27 07:55:37 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftjson.h>
#include <libft.h>

t_json_value_type	ft_json_evaluate_value_type(const char *src,
								const unsigned long length, unsigned long pos)
{
	if (src[pos] == 'n' && pos + 3 < length && src[pos + 1] == 'u' &&
			src[pos + 2] == 'l' && src[pos + 3] == 'l')
		return (null);
	if ((src[pos] == 'f' && pos + 4 < length && src[pos + 1] == 'a' &&
			src[pos + 2] == 'l' && src[pos + 3] == 's' && src[pos + 4] == 'e')
			|| (src[pos] == 't' && pos + 3 < length && src[pos + 1] == 'r' &&
			src[pos + 2] == 'u' && src[pos + 3] == 'e'))
		return (boolean);
	if (ft_isdigit(src[pos]) || src[pos] == '-' || src[pos] == '+')
	{
		if (ft_is_double(&src[pos]))
			return (number);
		else
			return (integer);
	}
	if (src[pos] == '"')
		return (string);
	if (src[pos] == '[')
		return (array);
	if (src[pos] == '{')
		return (object);
	return (none);
}
