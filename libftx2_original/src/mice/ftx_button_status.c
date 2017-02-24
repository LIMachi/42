/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_button_status.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 11:28:19 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/21 17:12:29 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <libftx.h>

int	*ftx_button_status(int button)
{
	if (button < 0 || button >= 10 || ftx_data()->focused_window == NULL)
		return (NULL);
	return (&ftx_data()->focused_window->mice.keymap[button].status);
}
