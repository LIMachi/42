/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vfnprintf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 20:43:11 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/28 01:55:58 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int	ft_vfnprintf(FILE *stream, size_t size, const char *format, va_list ap)
{
	t_printf_data	data;

	data = (t_printf_data){.format = format, .f_pos = -1, .size = size,
		.len = 0, .b_pos = 0, .buffer = {0}, .fss.stream = stream,
		.buffer_dumper = to_stream};
	return (main_printf(&data, ap));
}
