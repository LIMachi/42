/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_key_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 13:28:41 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/21 17:18:52 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <libftx.h>

int	*ftx_key_status(int key)
{
	if (key < 0 || key >= KEYMAP_SIZE)
		return (NULL);
	return (&ftx_data()->keymap[key].status);
}
