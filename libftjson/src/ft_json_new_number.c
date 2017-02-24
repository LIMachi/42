/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_json_new_number.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 17:52:37 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/27 07:55:46 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftjson.h>
#include <libft.h>

inline static int	sf_json_jump_number(const char *src,
								const unsigned long length, unsigned long pos)
{
	(void)length;
	if (src[pos] == '-' || src[pos] == '+')
		++pos;
	while (ft_isdigit(src[pos]))
		++pos;
	if (src[pos] == '.')
	{
		++pos;
		while (ft_isdigit(src[pos]))
			++pos;
	}
	if (src[pos] == 'e' || src[pos] == 'E')
	{
		++pos;
		if (src[pos] == '-' || src[pos] == '+')
			++pos;
		while (ft_isdigit(src[pos]))
			++pos;
	}
	if (ft_isinset(src[pos], "fFdD"))
		++pos;
	return (pos);
}

t_json_value		*ft_json_new_number(const char *src,
		const unsigned long length, unsigned long *pos, t_json_value *parent)
{
	t_json_value	*out;

	if (src == NULL || (src[*pos] != '+' && src[*pos] != '-' &&
			!ft_isdigit(src[*pos])) || *pos >= length)
		return (NULL);
	if ((out = (t_json_value*)ft_malloc(sizeof(t_json_value))) == NULL)
		return (NULL);
	if (ft_is_double(&src[*pos]))
	{
		out->type = number;
		if ((out->ptr = ft_malloc(sizeof(double))) == NULL)
			return (ft_free(out));
		*(double*)out->ptr = ft_atod(&src[*pos]);
	}
	else
	{
		out->type = integer;
		if ((out->ptr = ft_malloc(sizeof(int))) == NULL)
			return (ft_free(out));
		*(int*)out->ptr = ft_atoi_extended(&src[*pos]);
	}
	out->parent = parent;
	*pos = sf_json_jump_number(src, length, *pos);
	return (out);
}
