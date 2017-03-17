/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 20:05:01 by hmartzol          #+#    #+#             */
/*   Updated: 2017/03/17 07:33:11 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	parse_number(const char *format, int *number, int *arg_number, int *pos)
{
	int	tmp;

	if (format[*pos] == '*')
	{
		if (format[++(*pos)] >= '1' && format[*pos] <= '9')
		{
			*number = 0;
			tmp = *pos;
			while (format[tmp] >= '0' && format[tmp] <= '9')
				*number = (*number) * 10 + format[tmp++] - '0';
			(format[tmp] == '$') ? ((*pos = tmp + 1) && --(*number)) :
								(*number = (*arg_number)++);
		}
		else
			*number = (*arg_number)++;
		return (1);
	}
	if (format[*pos] >= '1' && format[*pos] <= '9')
	{
		*number = 0;
		while (format[*pos] >= '0' && format[*pos] <= '9')
			*number = (*number) * 10 + format[(*pos)++] - '0';
		return (0);
	}
	return (-1);
}
