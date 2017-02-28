/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 20:05:01 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/28 01:54:39 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int	parse_number(const char *format, int *number, int *arg_number, int *pos)
{
	int	tmp;

	if (format[*pos] == '*')
	{
		if (ft_strcchr("123456789", format[++(*pos)]) != -1)
		{
			*number = 0;
			tmp = *pos;
			while (format[tmp] != '\0' && ft_isdigit(format[tmp]))
				*number = (*number) * 10 + format[tmp++] - '0';
			(format[tmp] == '$') ? (*pos = tmp + 1) :
								(*number = (*arg_number)++);
		}
		else
			*number = (*arg_number)++;
		return (1);
	}
	if (format[*pos] >= '1' && format[*pos] <= '9')
	{
		*number = 0;
		while (format[*pos] != '\0' && ft_isdigit(format[*pos]))
			*number = (*number) * 10 + format[(*pos)++] - '0';
		return (0);
	}
	return (-1);
}
