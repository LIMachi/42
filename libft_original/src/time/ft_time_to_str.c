/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time_to_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 16:28:04 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/19 00:48:54 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** indev
*/

char	*sf_time_to_str_weekday(t_time time, int verbose)
{
	char				*str;
	static const char	*ref[7][2] = {
		{TIME_DEFAULT_WEEKDAY_0, TIME_SHORT_WEEKDAY_0},
		{TIME_DEFAULT_WEEKDAY_1, TIME_SHORT_WEEKDAY_1},
		{TIME_DEFAULT_WEEKDAY_2, TIME_SHORT_WEEKDAY_2},
		{TIME_DEFAULT_WEEKDAY_3, TIME_SHORT_WEEKDAY_3},
		{TIME_DEFAULT_WEEKDAY_4, TIME_SHORT_WEEKDAY_4},
		{TIME_DEFAULT_WEEKDAY_5, TIME_SHORT_WEEKDAY_5},
		{TIME_DEFAULT_WEEKDAY_6, TIME_SHORT_WEEKDAY_6}};

	str = NULL;
	if (verbose & TIME_WEEKDAY && !(verbose & TIME_WEEKDAY_NAME))
		str = ft_itoa(time.weekday);
	if (verbose & TIME_WEEKDAY_NAME)
		str = ft_strdup(ref[time.weekday][(verbose & TIME_FORMAT_SHORT) != 0]);
	return (str);
}

char	*sf_time_to_str_month(t_time time, int verbose)
{
	char				*str;
	static const char	*ref[12][2] = {
		{TIME_DEFAULT_MONTH_0, TIME_SHORT_MONTH_0},
		{TIME_DEFAULT_MONTH_1, TIME_SHORT_MONTH_1},
		{TIME_DEFAULT_MONTH_2, TIME_SHORT_MONTH_2},
		{TIME_DEFAULT_MONTH_3, TIME_SHORT_MONTH_3},
		{TIME_DEFAULT_MONTH_4, TIME_SHORT_MONTH_4},
		{TIME_DEFAULT_MONTH_5, TIME_SHORT_MONTH_5},
		{TIME_DEFAULT_MONTH_6, TIME_SHORT_MONTH_6},
		{TIME_DEFAULT_MONTH_7, TIME_SHORT_MONTH_7},
		{TIME_DEFAULT_MONTH_8, TIME_SHORT_MONTH_8},
		{TIME_DEFAULT_MONTH_9, TIME_SHORT_MONTH_9},
		{TIME_DEFAULT_MONTH_10, TIME_SHORT_MONTH_10},
		{TIME_DEFAULT_MONTH_11, TIME_SHORT_MONTH_11}};

	str = NULL;
	if (verbose & TIME_MONTH && !(verbose & TIME_MONTH_NAME))
		str = ft_itoa(time.month);
	if (verbose & TIME_MONTH_NAME)
		str = ft_strdup(ref[time.month][(verbose & TIME_FORMAT_SHORT) != 0]);
	return (str);
}

char	*ft_time_to_str(t_time time, int verbose)
{
	char	buffer[256];

	ft_bzero(buffer, 256);
	(void)time;
	(void)verbose;
	return (ft_strdup(buffer));
}
