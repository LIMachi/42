/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_key_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 12:56:42 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/21 17:18:45 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <libftx.h>

int	ftx_key_hook(int key, int (*callback)(int key, int status, void *data),
				void *data)
{
	if (key >= KEYMAP_SIZE)
	{
		ft_error(EINVAL, "ftx_key_hook got wrong key code\n");
		return (-1);
	}
	ftx_data()->keymap[key] = (t_key_data){
		.status = FTX_KEY_STATUS_RELEASED,
		.callback = callback,
		.data = data,
		.tick = !0u};
	return (0);
}
