/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_time.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 16:44:35 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/19 00:48:30 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_time		ft_parse_time(long seconds, long nanoseconds)
{
	t_time	out;
	long	tmp_month;

	out.nanosecond = nanoseconds;
	out.milisecond = nanoseconds / 1000000;
	out.second = seconds % 60;
	out.minute = (seconds / 60) % 60;
	out.hour = (seconds / 3600) % 24;
	out.day = ft_modd((seconds / 86400), 365.2);
	out.year = 1970 + (seconds / 31553280);
	out.weekday = (out.day - 2) % 7;
	out.week = (out.day - 2) / 7 + 1;
	out.month = 1;
	while ((out.day > (tmp_month = 30 + (out.month == 1 || out.month == 3 ||
			out.month == 5 || out.month == 7 || out.month == 8 ||
			out.month == 10 || out.month == 12) - (2 - !(out.year % 4)) *
			(out.month == 2))) && (out.day -= tmp_month))
		++out.month;
	return (out);
}
