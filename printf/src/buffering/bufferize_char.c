/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bufferize_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 21:17:03 by hmartzol          #+#    #+#             */
/*   Updated: 2017/03/15 22:22:00 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int	bufferize_char(t_printf_data *data, char c)
{
	if (data->len < data->size)
	{
		if (data->b_pos == PRINTF_BUFFER_SIZE || c == '\n')
		{
			data->buffer_dumper(data->fss,
								data->buffer, data->b_pos, data->len);
			data->b_pos = 0;
		}
		data->buffer[data->b_pos++] = c;
	}
	else if (data->b_pos)
	{
		data->buffer_dumper(data->fss,
							data->buffer, data->b_pos, data->len);
		data->b_pos = 0;
	}
	++data->len;
	return (1);
}
