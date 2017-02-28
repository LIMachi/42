/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_printf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 21:37:46 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/28 09:00:06 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int	apply_balise(t_printf_data *data)
{
	(void)data;
	return (1);
}

int	main_printf(t_printf_data *data, va_list ap)
{
	int					tmp;
	int					formn;
	t_printf_form		*forms;

	formn = 0;
	forms = NULL;
	while (data->len < data->size && data->format[++data->f_pos] != '\0')
		if (data->format[data->f_pos] == '%' && data->format[++data->f_pos] != '%')
		{
			if (data->format[data->f_pos] == '{' && apply_balise(data))
				continue;
			if ((forms == NULL && !(tmp = 0)) && ((forms = parse_forms(
data->format + data->f_pos - 1, &tmp)) == NULL || parse_args(forms, ap, tmp)))
				return (-1);
			/*data->len += */dn_put_arg(data, forms, formn++, &data->f_pos);
		}
		else
			bufferize_char(data, data->format[data->f_pos]);
	data->buffer_dumper(data->fss, data->buffer, data->b_pos, data->len);
	data->len += data->b_pos;
	if (forms != NULL)
		ft_free(forms);
	return (data->len);
}
