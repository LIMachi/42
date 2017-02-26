/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bufferize_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lee <lee@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 20:51:04 by lee               #+#    #+#             */
/*   Updated: 2017/02/25 23:24:27 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void	bufferize_str(t_printf_data *data, char *str, size_t size)
{
	size_t	tmp;

	if (size == 0)
		return ;
	if (size == 1)
	{
		bufferize_char(data, *str);
		return ;
	}
//	if (data->len + data->)
	if (data->buffer_pos + size >= data->buffer_size)
	{
		tmp = (data->buffer_size - data->buffer_pos);
		data->buffer_dumper(data->fss, data->buffer, data->buffer_pos, data->len);
		data->buffer_dumper(data->fss, str, tmp, data->len);
		bufferize_str(data, str + tmp, size - tmp);
	}
	else
	{
		ft_memmove(data->buffer + data->buffer_pos, str, size);
		data->buffer_pos += size;
	}
}
