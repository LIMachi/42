/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vsnprintf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 20:14:06 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/28 01:56:09 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int	ft_vsnprintf(char *str, size_t size, const char *format, va_list ap)
{
	t_printf_data	data;

	data = (t_printf_data){.format = format, .f_pos = -1, .size = size,
		.len = 0, .b_pos = 0, .buffer = {0}, .fss.str = str,
		.buffer_dumper = to_str};
	if (str == NULL)
		data.buffer_dumper = to_null;
	return (main_printf(&data, ap));
}
