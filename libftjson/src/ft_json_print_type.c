/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_json_print_type.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 02:54:11 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/27 07:56:08 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftjson.h>
#include <libft.h>

t_json_value_type	ft_json_print_type(t_json_value *node)
{
	char	*str;

	if (node == NULL)
	{
		ft_putendl("node is NULL pointed");
		return (none);
	}
	node->type == none ? str = "none" : 0;
	node->type == null ? str = "null" : 0;
	node->type == boolean ? str = "boolean" : 0;
	node->type == array ? str = "array" : 0;
	node->type == object ? str = "object" : 0;
	node->type == integer ? str = "integer" : 0;
	node->type == number ? str = "number" : 0;
	node->type == string ? str = "string" : 0;
	ft_putstr("node is of type: '");
	ft_putstr(str);
	ft_putstr("'\n");
	return (node->type);
}
