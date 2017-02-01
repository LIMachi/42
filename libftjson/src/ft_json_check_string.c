/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_json_check_string.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 03:54:48 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/27 07:55:26 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftjson.h>
#include <libft.h>

unsigned int	ft_json_check_string(t_json_value *v, const int nb_strings,
									char **str, const int default_return)
{
	t_json_string	*s;
	int				i;

	if (v == NULL || v->type != string || str == NULL || nb_strings <= 0 ||
		(s = (t_json_string*)v->ptr) == NULL || s->length == 0 ||
		s->ptr == NULL)
		return (default_return);
	i = -1;
	while (++i < nb_strings)
		if (str[i] != NULL && ft_strcmp((char*)str[i], s->ptr) == 0)
			break ;
	if (i < nb_strings)
		return (i);
	return (default_return);
}
