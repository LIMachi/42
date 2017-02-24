/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_material.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 02:00:39 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/30 03:01:09 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_material			default_material(void)
{
	t_material	out;

	out.color = (cl_float4){.x = 1.0f, .y = 1.0f, .z = 1.0f, .w = 0.0f};
	out.diffuse = 1.0f;
	out.specular = 1.0f;
	out.reflection = 0.0f;
	out.perturbation.normal = 0.0f;
	out.perturbation.color = NONE;
	out.texture.info_index = -1;
	out.texture.stretch = (cl_float2){.x = 1.0f, .y = 1.0f};
	return (out);
}
