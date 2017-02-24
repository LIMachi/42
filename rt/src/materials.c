/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 17:20:29 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/26 04:38:56 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_material_holder	*materials(void)
{
	static t_material_holder	m = {.nb_materials = 0, .name = NULL,

	.materials = NULL};
	return (&m);
}
