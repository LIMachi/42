/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vdnprintf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 20:10:35 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/26 22:26:01 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

/*
int	ft_vdnprintf(int fd, size_t size, const char *format, va_list ap)
{
	size_t				len;
	int					tmp;
	t_printf_put_arg	parg;
	int					formn;

	len = 0;
	formn = 0;
	parg = (t_printf_put_arg){.forms = NULL, .size = size, .format = format,
							.pos = -1};
	while (len < size && format[++parg.pos] != '\0')
	{
		if (format[parg.pos] == '%' && format[++parg.pos] != '%')
		{
			if (parg.forms == NULL && !(tmp = 0))
				if ((parg.forms = parse_forms(format + parg.pos - 1, &tmp))
						== NULL || parse_args(parg.forms, ap, tmp))
					return (-1);
			len += dn_put_arg(&parg, formn++, len, fd);
		}
		else
			len += write(fd, format + parg.pos, 1);
	}
	if (parg.forms != NULL)
		ft_free(parg.forms);
	return (len);
}
*/

int	ft_vdnprintf(int fd, size_t size, const char *format, va_list ap)
{
	t_printf_data	data;

	data = (t_printf_data){.format = format, .f_pos = -1, .size = size,
	.len = 0, .b_pos = 0, .buffer = {0}, .fss.fd = fd, .buffer_dumper = to_fd};
	return (main_printf(&data, ap));
}
