/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_is_button_press.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 20:42:57 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/09 17:20:09 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftx.h>

int	ftx_is_button_press(int button_code)
{
	t_ftx_data	*data;

	if ((data = ftx_data(GDX_ACCES)) == NULL)
		return (-1);
	if (button_code < 0)
		return (data->mice.map[-button_code]);
	return (data->keymap[button_code]);
}
