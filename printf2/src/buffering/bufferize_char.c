/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bufferize_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lee <lee@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 21:17:03 by lee               #+#    #+#             */
/*   Updated: 2017/02/25 23:24:33 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void	bufferize_char(t_printf_data *data, char c)
{
	if (data->len + data->buffer_pos < data->max_len)
	{
		if (data->buffer_pos == data->buffer_size)
		{
			data->buffer_dumper(data->fss, data->buffer, data->buffer_pos, data->len);
			data->len += data->buffer_pos;
			data->buffer_pos = 0;
		}
		data->buffer[data->buffer_pos++] = c;
	}
	else
	{
		if (data->buffer_pos)
		{
			data->buffer_dumper(data->fss, data->buffer, data->buffer_pos, data->len);
			data->len += data->buffer_pos;
			data->buffer_pos = 0;
		}
	}
}
