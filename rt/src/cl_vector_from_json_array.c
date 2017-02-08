/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_vector_from_json_array.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 03:54:02 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/27 08:01:48 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

cl_float4			cl_vector_from_json_array(t_json_value *node,
											cl_float4 default_return)
{
	t_json_value		**ar;
	cl_float4			out;
	t_json_value_type	*la_norm_me_troll;

	la_norm_me_troll = (t_json_value_type[3])
		{integer | number, integer | number, integer | number};
	if (!ft_json_check_array_types(node, 3, la_norm_me_troll))
		return (default_return);
	ar = ((t_json_array*)node->ptr)->value;
	out.x = ar[0]->type == integer ?
		(cl_float) * (int*)ar[0]->ptr : (cl_float) * (double*)ar[0]->ptr;
	out.y = ar[1]->type == integer ?
		(cl_float) * (int*)ar[1]->ptr : (cl_float) * (double*)ar[1]->ptr;
	out.z = ar[2]->type == integer ?
		(cl_float) * (int*)ar[2]->ptr : (cl_float) * (double*)ar[2]->ptr;
	out.w = 0.0f;
	return (out);
}
