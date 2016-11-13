/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 18:53:11 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/08 18:54:27 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftx.h>

t_ftx_data	*ftx_init(void)
{
	if (ftx_data(GDX_NEW) == NULL)
		return (NULL);
	return (init_mlx_data());
}
