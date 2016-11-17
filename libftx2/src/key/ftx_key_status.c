/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_key_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 13:28:41 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/17 14:15:41 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftx.h>

int	*ftx_key_status(int key)
{
	if (key >= KEYMAP_SIZE)
		return (NULL);
	return (&ftx_data()->keymap[key].status);
}
