/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_loop_hook.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 19:30:22 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/07 19:55:25 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <libftx.h>

int	ftx_loop_hook(int (*loop_callback)(t_ftx_data *data))
{
	if (ftx_data() == NULL)
		return (-1);
	if (ftx_data()->loop_callback != NULL)
		return (1);
	ftx_data()->loop_callback = loop_callback;
	return (0);
}
