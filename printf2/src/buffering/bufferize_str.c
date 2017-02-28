/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bufferize_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 20:51:04 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/28 02:26:13 by hmartzol         ###   ########.fr       */
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
	if (data->b_pos + size >= PRINTF_BUFFER_SIZE)
	{
		tmp = (PRINTF_BUFFER_SIZE - data->b_pos);
		data->buffer_dumper(data->fss, data->buffer, data->b_pos, data->len);
		data->buffer_dumper(data->fss, str, tmp, data->len);
		bufferize_str(data, str + tmp, size - tmp);
	}
	else
	{
		ft_memmove(data->buffer + data->b_pos, str, size);
		data->b_pos += size;
	}
}
